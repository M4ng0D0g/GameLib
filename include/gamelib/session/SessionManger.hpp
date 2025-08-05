#pragma once

#include "interface/ISession.hpp"
#include "gamelib/utils/Uuid.hpp"
#include "gamelib/utils/Time.hpp"
#include <atomic>
#include <memory>
#include <unordered_map>

using uuid = gamelib::utils::uuid;

namespace gamelib::session {

	class SessionManager {
	public:
		virtual ~SessionManager() noexcept = default;

		// --------------------------------------------------------------------------------

		// TcpSession::SPtr createSession(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
		// 	std::string uuid = Utils::generateUuid();
		// 	auto session = TcpSession::create(uuid, std::move(socket));
		// 	sessions_[uuid] = session;
		// 	return session;
		// }

		void registerSession(const uuid& id, std::shared_ptr<interface::ISession> session) {
			sessions_[id] = std::move(session);
		}
		
		void unregisterSession(const uuid& id) {
			sessions_.erase(id);
		}

		// --------------------------------------------------------------------------------

		std::shared_ptr<interface::ISession> find(const uuid& id) {
			auto it = sessions_.find(id);
			return it != sessions_.end() ? it->second : nullptr;
		}

		template <typename T>
		std::shared_ptr<T> findTyped(const uuid& id) const {
			auto it = sessions_.find(id);
			if (it == sessions_.end()) return nullptr;

			auto casted = std::dynamic_pointer_cast<T>(it->second);
			if (!casted) {
				// log warning
				return nullptr;
			}
			else return casted;
		}

		// --------------------------------------------------------------------------------

		void tick(std::chrono::steady_clock::time_point now) {
			// 預設無動作；若需要過期清理，可在這裡遍歷 sessions_
			// for (auto it = sessions_.begin(); it != sessions_.end(); /*...*/) { ... }

			const auto timeout = std::chrono::minutes(5);

			for (auto it = sessions_.begin(); it != sessions_.end();) {
				if (now - it->second->lastActive() > timeout) {
					it->second->close();
					it = sessions_.erase(it);
				}
				else ++it;
			}
		}

		// --------------------------------------------------------------------------------

		// --- 也可以提供「型別安全」的額外 API（非介面的一部分） ---
		// void registerTyped(const Utils::uuid& id, SessionT_SPtr session) {
		// 	sessions_[id] = std::move(session);
		// }

		

		std::size_t size() const noexcept {
			return sessions_.size();
		}
		
		// Session::S_Ptr SessionManager::createSession(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
		// 	Utils::uuid id = Utils::generateUuid();
		// 	auto session = Session::create(id, std::move(socket));
		// 	sessions_[id] = session;
		// 	return session;
		// }
		

		// Session::Token create(Session::Token token, ENetPeer* peer);

		// //超過時間清理(用Time)
		// void remove(Session::Token token);
		// void cleanCheck();
		// //Peer斷線
		// void disconnect(ENetPeer*);
	protected:
		// Time::Time timeToClean_; //TODO
		// std::atomic<Session::Token> nextToken_{1};

		// 注意：需要為 Utils::uuid 提供 hash 與 ==，否則 unordered_map 用不了
		std::unordered_map<uuid, std::shared_ptr<interface::ISession>> sessions_;
		// std::unordered_map<ENetPeer*, Session::Ptr> peerSessions_;
		
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


// class UdpSessionManager : public Base::SessionManagerBase<UdpSession> {
// public:
//     /* 依需求，可用 remoteEndpoint 作 index */
//     UdpSession::Ptr findOrCreate(const boost::asio::ip::udp::endpoint& ep) {
//         auto key = ep.address().to_string() + ":" + std::to_string(ep.port());
//         auto s   = this->find(key);
//         if (!s) {
//             s = std::make_shared<UdpSession>(ep);
//             this->add(s);
//         }
//         return s;
//     }

//     void tick(std::chrono::steady_clock::time_point now) override {
//         const auto ttl = std::chrono::seconds(30);   // UDP 一般較短
//         for (auto it = sessions_.begin(); it != sessions_.end(); ) {
//             if (now - it->second->lastActive() > ttl) {
//                 it = sessions_.erase(it);
//             } else ++it;
//         }
//     }
// };