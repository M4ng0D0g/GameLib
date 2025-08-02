#pragma once

#include <string>

namespace GameLib::Network::Interface {

	class IClient {
	public:
		virtual ~IClient() = default;

		virtual void send(const std::string& message) = 0;


	};

}