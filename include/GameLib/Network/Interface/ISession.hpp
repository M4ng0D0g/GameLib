#pragma once

#include "GameLib/Network/Common/Message.hpp"

namespace GameLib::Network::Interface {
	
	class ISession {
	public:
		virtual ~ISession() = default;

		virtual void start() = 0;
		virtual void send(const Common::Message& msg) = 0;

		virtual const std::string& id() const noexcept = 0;
		virtual bool isConnected() const noexcept = 0;

	};

}