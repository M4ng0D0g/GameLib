#pragma once

#include <string>

namespace gamelib::network::interface {

	class IClient {
	public:
		virtual ~IClient() = default;

		virtual void send(const std::string& message) = 0;


	};

}