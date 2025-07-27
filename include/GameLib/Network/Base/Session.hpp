#pragma once

#include "GameLib/Network/Interface/ISession.hpp"
#include "GameLib/Utils/Uuid.hpp"
#include "GameLib/Utils/Time.hpp"
#include "SessionManger.hpp"
#include <boost/asio.hpp>
#include <vector>
#include <queue>
#include <atomic>
#include <memory>

namespace GameLib::Network::Base {

	class Session : public Interface::ISession, public std::enable_shared_from_this<Session> {
	protected:
		void close();
		void doRead();
		void doWrite();

		Utils::uuid sessionId_;
		// boost::asio::ip::tcp::socket socket_;
		std::vector<std::byte> rxBuffer_;
		std::deque<std::vector<std::byte>> txQueue_;
		std::atomic<bool> connected_{false};

		boost::asio::strand<boost::asio::io_context::executor_type> strand_;
		SessionManager::S_Ptr manager_;
		Utils::StedayClock::time_point lastActive_;

	public:
		using S_Ptr = std::shared_ptr<Session>;

		explicit Session(SessionManager::S_Ptr manager)
			: manager_(std::move(manager)), sessionId_(Utils::generateUuid()), connected_(false) {}

		virtual void start() = 0;
		virtual void send(const Common::Message& msg) = 0;

		const std::string& id() const noexcept {
			return sessionId_;
		}
		bool isConnected() const noexcept {
			return connected_.load();
		}
	};
}