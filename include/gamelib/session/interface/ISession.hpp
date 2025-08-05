#pragma once

#include "gamelib/network/Message.hpp"
#include <chrono>

namespace gamelib::session::interface {

	class ISession {
	public:
		virtual ~ISession() noexcept = default;

		virtual void start() = 0;
		//void resume(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
		virtual void close() = 0;
		virtual void send(const network::Message& msg) = 0;

		// virtual const std::string& id() const = 0;
		virtual const std::chrono::_V2::steady_clock::time_point lastActive() = 0;
		// virtual bool isConnected() const = 0;
		
	};
}