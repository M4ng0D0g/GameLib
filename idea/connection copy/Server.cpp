#include "connection/Server.h"
#include "connection/Packet.h"
#include "connection/PacketBuilder.h"
#include "connection/PacketHandler.h"
#include "connection/Logger.h"
#include "connection/ClientSession.h"
#include "connection/event/EventFactory.h"

Server::Server(const Config& cfg) {
	cfg_ = cfg;

	ENetAddress addr;
	addr.host = cfg_.host;
	addr.port = cfg_.port;
	host_ = enet_host_create(&addr, cfg_.maxClients, 1, 0, 0);
	if (!host_) throw std::runtime_error{"Failed to create ENet server"};

	serverId_ = uuid::generateV4();
	Logger::server_create(cfg_.host, cfg_.port);
}

void Server::serviceOnce(enet_uint32 timeoutMs) {
	sessionManager_.cleanCheck();

	static ENetEvent event;
	while(enet_host_service(host_, &event, timeoutMs) > 0) {
		switch(event.type) {
			case ENET_EVENT_TYPE_CONNECT: handleConnect(event); break;
			case ENET_EVENT_TYPE_DISCONNECT: handleDisconnect(event); break;
			case ENET_EVENT_TYPE_RECEIVE: handleReceive(event); break;
			default: break;
		}
	}
}


void Server::handleConnect(ENetEvent& event) {
	if(!running_) { enet_peer_disconnect_now(event.peer, 0); return; }
	Logger::server_connect(event);

	PacketBuilder builder(PacketBuilder::Type::Welcome);
	Packet packet = builder.with("serverId", serverId_).build();
	send(event.peer, packet);
}

void Server::handleDisconnect(ENetEvent& event) {
	Logger::server_disconnect(event);
	sessionManager_.disconnect(event.peer);
}

void Server::handleReceive(ENetEvent& event) {
	Logger::server_receivePacket(event);
				
	auto obj = PacketHandler::parseObject(event);
	auto session = sessionManager_.getSession(event.peer);

	if(auto e = EventFactory::create(session, obj)) bus_.dispatch(e);
	else Logger::warn("EventFactory failed to create event from packet: ", obj.dump());

	enet_packet_destroy(event.packet);
}

void Server::run() {
	if (!host_) return;
	running_.store(true);
	while(running_) serviceOnce(0);
}

void Server::stop() {
	if (!host_ || !running_) return;

	Logger::info("Stopping server...");
	running_.store(false);

	// 通知所有連線的 client 進行正常斷線
	for (size_t i = 0; i < host_->peerCount; ++i) {
		ENetPeer* peer = &host_->peers[i];
		if (peer->state != ENET_PEER_STATE_DISCONNECTED) enet_peer_disconnect(peer, 0);
	}

	// 等待一段時間處理 disconnect 回應
	constexpr enet_uint32 gracefulTimeoutMs = 3000;
	const auto start = std::chrono::steady_clock::now();

	while (true) {
		serviceOnce(100); // 處理 enet_event，例如 disconnect 回來的事件

		bool allDisconnected = true;
		for (size_t i = 0; i < host_->peerCount; ++i) {
			if (host_->peers[i].state != ENET_PEER_STATE_DISCONNECTED) {
				allDisconnected = false;
				break;
			}
		}

		auto elapsed = std::chrono::steady_clock::now() - start;
		if (allDisconnected || elapsed > std::chrono::milliseconds(gracefulTimeoutMs)) break;
	}

	// 強制關閉所有還沒斷的 peer（保險）
	for (size_t i = 0; i < host_->peerCount; ++i) {
		ENetPeer* peer = &host_->peers[i];
		if (peer->state != ENET_PEER_STATE_DISCONNECTED) enet_peer_disconnect_now(peer, 0);
	}

	enet_host_destroy(host_);
	host_ = nullptr;

	Logger::server_stop();
}


ENetPacket* Server::toENetPacket(const Packet& packet) {
	auto msg = PacketHandler::parseObject(packet).dump();
	return enet_packet_create(msg.data(), msg.size(), ENET_PACKET_FLAG_RELIABLE);
}

void Server::send(ENetPeer* peer, const Packet& packet) {
	enet_peer_send(peer, 0, toENetPacket(packet));
}

void Server::broadcast(const Packet& packet) {
	enet_host_broadcast(host_, 0, toENetPacket(packet));
	enet_host_flush(host_);
}