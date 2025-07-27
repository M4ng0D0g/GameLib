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
		static_assert(std::is_base_of_v<Base::Session, SessionT>,"SessionT must derive from Base::Session");

	public:
		using SessionT_SPtr = std::shared_ptr<SessionT>;
		using BaseSession_SPtr  = std::shared_ptr<Base::Session>;

		// --------------------------------------------------------------------------------

		virtual ~SessionManager() noexcept override = default;

		// --------------------------------------------------------------------------------

		// void createSession() {}
		void registerSession(const Utils::uuid& id, SessionT_SPtr session) override {
			sessions_[id] = std::move(session);
		}
		void unregisterSession(const Utils::uuid& id) override {
			sessions_.erase(id);
		}

		// --------------------------------------------------------------------------------

		BaseSession_SPtr find(const Utils::uuid& id) override {
			auto it = sessions_.find(id);
			if (it == sessions_.end()) return nullptr;
			return std::static_pointer_cast<Base::Session>(it->second);
		}
		SessionT_SPtr findTyped(const Utils::uuid& id) const {
			auto it = sessions_.find(id);
			return it != sessions_.end() ? it->second : nullptr;
		}

		// --------------------------------------------------------------------------------

		void tick(std::chrono::steady_clock::time_point now) override {
			// 預設無動作；若需要過期清理，可在這裡遍歷 sessions_
			// for (auto it = sessions_.begin(); it != sessions_.end(); /*...*/) { ... }
		}

		// --------------------------------------------------------------------------------

		// --- 也可以提供「型別安全」的額外 API（非介面的一部分） ---
		// void registerTyped(const Utils::uuid& id, SessionT_SPtr session) {
		// 	sessions_[id] = std::move(session);
		// }

		

		std::size_t size() const noexcept { return sessions_.size(); }
		
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
		std::unordered_map<Utils::uuid, SessionT_SPtr> sessions_;
		// std::unordered_map<ENetPeer*, Session::Ptr> peerSessions_;
		
	};
}

