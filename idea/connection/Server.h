#pragma once

#include "ENetContext.h"

#include "SessionManager.h"
#include "common/event/EventBus.h"
#include "utils/uuid.h"
#include <enet/enet.h>
#include <string>
#include <atomic>
#include <unordered_map>

// ***************************************************************************/

class Server {
public:
	struct Config { enet_uint32 host; enet_uint16 port; size_t maxClients; };

private:
	std::atomic<bool> running_ = false;
	
	ENetContext context_;
	uuid::uuidV4 serverId_;
	ENetHost* host_ = nullptr;
	Config cfg_;

	SessionManager sessionManager_;
	EventBus bus_;

public:
	Server(const Config& cfg);

	void run();
	void stop();

	void send(ENetPeer*, const Packet&);
	void broadcast(const Packet&);

private:
	void serviceOnce(enet_uint32 timeoutMs);
	void handleConnect(ENetEvent& event);
	void handleDisconnect(ENetEvent& event);
	void handleReceive(ENetEvent& event);

	ENetPacket* toENetPacket(const Packet& packet);
};