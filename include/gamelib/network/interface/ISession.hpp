#pragma once

#include "GameLib/Network/Common/Message.hpp"

namespace GameLib::Network::Interface {
	
	class ISession {
	public:
		virtual ~ISession() noexcept = default;

		virtual void start() = 0;
		virtual void close() = 0;
		virtual void send(const Common::Message& msg) = 0;

		// virtual const std::string& id() const = 0;
		// virtual const std::string& lastActive
		// virtual bool isConnected() const = 0;

	};

}