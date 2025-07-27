#pragma once

#include "GameLib/Network/Interface/IClient.hpp"
#include <boost/asio.hpp>
#include <thread>
#include <atomic>

namespace GameLib::Network::Base {

	class Client : public Interface::IClient {
	public:
		virtual ~Client() = default;

	protected:
		boost::asio::io_context ioContext_;
		std::thread ioThread_;
		std::atomic<bool> connected_{false};
	};

}