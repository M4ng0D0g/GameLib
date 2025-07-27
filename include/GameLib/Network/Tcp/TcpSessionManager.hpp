#pragma once

#include "GameLib/Network/Base/SessionManger.hpp"
#include "TcpSession.hpp"
#include <atomic>
#include <memory>
#include <unordered_map>

using namespace GameLib::Utils;

// ***************************************************************************/

namespace GameLib::Network::Tcp {

	class TcpSessionManager : public Base::SessionManager<TcpSession> {
	public:
		using SPtr = std::shared_ptr<TcpSessionManager>;

		// --------------------------------------------------------------------------------

		TcpSession::SPtr createSession(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
			std::string uuid = Utils::generateUuid();
			auto session = TcpSession::create(uuid, std::move(socket));
			sessions_[uuid] = session;
			return session;
		}

		// --------------------------------------------------------------------------------

		void tick(std::chrono::steady_clock::time_point now) override {
			const auto timeout = std::chrono::minutes(5);

			for (auto it = sessions_.begin(); it != sessions_.end();) {
				if (now - it->second->lastActive() > timeout) {
					it->second->close();
					it = sessions_.erase(it);
				} else {
					++it;
				}
			}
		}

	};
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