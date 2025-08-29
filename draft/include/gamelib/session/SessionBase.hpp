#pragma once

#include "gamelib/utils/Uuid.hpp"
#include "gamelib/utils/Time.hpp"
#include "gamelib/session/SessionManger.hpp"
#include <boost/asio.hpp>
#include <vector>
#include <queue>
#include <atomic>
#include <memory>

using uuid = gamelib::utils::uuid;

namespace gamelib::session {

	using Token = uint32_t;
	
}

namespace gamelib::session::base {

	class BaseSession {
	public:
		virtual ~BaseSession() noexcept = default;

		const Token& token() const {
			return token_;
		}
		const uuid& id() const {
			return id_;
		}
		bool isConnected() const {
			return connected_.load();
		}
		const std::chrono::steady_clock::time_point& lastActive() const {
			return lastActive_;
		}

	protected:
		explicit BaseSession(Token token, uuid id = utils::generateUuid()) : token_(token), id_(id) {}
		// explicit Session(SessionManager::S_Ptr manager)
		// 	: manager_(std::move(manager)), sessionId_(Utils::generateUuid()), connected_(false) {}

		const Token token_;
		const uuid id_;
		std::atomic<bool> connected_{false};
		std::chrono::steady_clock::time_point lastActive_;

		// boost::asio::ip::tcp::socket socket_;
		std::vector<std::byte> rxBuffer_;
		std::deque<std::vector<std::byte>> txQueue_;
		

		boost::asio::strand<boost::asio::io_context::executor_type> strand_;
		// SessionManager::S_Ptr manager_;
		
		virtual void doRead() = 0;
		virtual void doWrite() = 0;

	
	};
}

/*
class ClientSession {
public:
	using Token = uint64_t;

	using Ptr = std::shared_ptr<ClientSession>;
	static Ptr create(Token token, ENetPeer* peer) {
		return Ptr(new ClientSession(token, peer));
	}

private:
	ClientSession(Token token, ENetPeer* peer) : token_(token), peer_(peer) {}

	Token token_;
	ENetPeer* peer_;
	bool isOnline_;
	Time::time offlineTime_; 

public:
	Token getToken() const noexcept { return token_; }
	ENetPeer* getPeer() const { return peer_; }
	void setPeer(ENetPeer* peer) { peer_ = peer; }

	void online() { isOnline_ = true; }
	void offline() { isOnline_ = false; offlineTime_ = Time::steadyNowMs(); }
	bool isOnline() { return isOnline_; }
	Time::time getOfflineTime() { return offlineTime_; }
};
*/