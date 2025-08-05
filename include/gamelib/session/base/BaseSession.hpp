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

namespace gamelib::session::base {

	class BaseSession {
	public:
		virtual ~BaseSession() noexcept = default;

		const uuid& id() const {
			return sessionId_;
		}
		bool isConnected() const {
			return connected_.load();
		}
		const std::chrono::steady_clock::time_point& lastActive() const {
			return lastActive_;
		}

	protected:
		explicit BaseSession(uuid id = utils::generateUuid()) : sessionId_(id) {}
		// explicit Session(SessionManager::S_Ptr manager)
		// 	: manager_(std::move(manager)), sessionId_(Utils::generateUuid()), connected_(false) {}

		uuid sessionId_;
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