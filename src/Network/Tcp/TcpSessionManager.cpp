#include "gamelib/network/SessionManager.hpp"

namespace GameLib::NetWork {

	Session::S_Ptr SessionManager::findById(const Uuid::uuid& uuid) {
		auto it = sessions_.find(uuid);
		return it != sessions_.end() ? it->second : nullptr;
	}

	Session::S_Ptr SessionManager::createSession(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
		std::string uuid = Uuid::generate();
		auto session = Session::create(uuid, std::move(socket));
		sessions_[uuid] = session;
		return session;
	}

	void registerSession(const Uuid::uuid& uuid, Session::S_Ptr session) {
		sessions_[uuid] = std::move(session);
	}

	// Session::Token SessionManager::create(ClientSession::Token token, ENetPeer* peer) {
	// 	if(tokenSessions_.contains(token)) {
	// 		auto session = tokenSessions_[token];
	// 		session->setPeer(peer);
	// 		session->online();
	// 		peerSessions_[peer] = session;
	// 		return token;
	// 	}
	// 	else {
	// 		tokenSessions_[nextToken_] = ClientSession::create(nextToken_, peer);
	// 		peerSessions_[peer] = tokenSessions_[nextToken_];
	// 		return nextToken_++;
	// 	}
	// }

	// void SessionManager::remove(ClientSession::Token token) {
	// 	if(tokenSessions_.contains(token)) tokenSessions_.erase(token);
	// }


	// void SessionManager::disconnect(ENetPeer* peer) {
	// 	if(peerSessions_.contains(peer)) {
	// 		peerSessions_[peer]->offline();
	// 		peerSessions_.erase(peer);
	// 	}
	// }


	// void SessionManager::disconnect(ClientSession::Token token) {
	// 	if(tokenSessions_.contains(token)) {
	// 		tokenSessions_[token]->offline();
	// 	}
	// }

	// void SessionManager::cleanCheck() {
	// 	auto now = Time::steadyNowMs();
	// 	for(auto& [token, session] : tokenSessions_) {
	// 		if(!session->isOnline() && (now - session->getOfflineTime() >= 60000)) remove(token);
	// 	}
	// }

}

