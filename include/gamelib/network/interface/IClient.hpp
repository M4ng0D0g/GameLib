#pragma once

#include <string>

namespace gamelib::network::interface {

	class IClient {
	public:
		virtual ~IClient() = default;

		virtual bool connect() = 0;
		virtual void send(const std::string& message) = 0;


	};

}