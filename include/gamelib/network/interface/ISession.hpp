#pragma once

#include "gamelib/network/common/Message.hpp"
#include <chrono>

namespace gamelib::network::interface {
	
	class ISession {
	public:
		virtual ~ISession() noexcept = default;

		virtual void start() = 0;
		virtual void close() = 0;
		virtual void send(const common::Message& msg) = 0;

		// virtual const std::string& id() const = 0;
		virtual const std::chrono::_V2::steady_clock::time_point lastActive() = 0;
		// virtual bool isConnected() const = 0;

	};

}