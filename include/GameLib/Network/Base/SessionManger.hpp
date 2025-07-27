#pragma once

#include "GameLib/Network/Interface/ISessionManager.hpp"
#include "GameLib/Utils/Uuid.hpp"
#include "GameLib/Utils/Time.hpp"
#include <atomic>
#include <memory>
#include <unordered_map>

namespace GameLib::Network::Base {

	template <typename SessionT>
	class SessionManager : public Interface::ISessionManager {
	public:
		using S_Ptr = std::shared_ptr<SessionManager>;
		using SessionPtr = std::shared_ptr<SessionT>;

	protected:
		// Time::Time timeToClean_; //TODO
		// std::atomic<Session::Token> nextToken_{1};

		std::unordered_map<Utils::uuid, SessionPtr> sessions_;
		// std::unordered_map<ENetPeer*, Session::Ptr> peerSessions_;
		
	public:
		virtual ~SessionManagerBase() = default;

		virtual void registerSession(const Utils::uuid& id, SessionPtr session) override {
			sessions_[id] = std::move(session);
		}
		virtual void unregisterSession(const Utils::uuid& id) override {
			sessions_.erase(id);
		}
		SessionPtr findById(const Utils::uuid& id) {
			auto it = sessions_.find(id);
			return it != sessions_.end() ? it->second : nullptr;
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

	};
}

