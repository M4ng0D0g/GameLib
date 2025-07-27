#pragma once

#include "GameLib/Network/Interface/IServer.hpp"
#include "GameLib/Utils/Uuid.hpp"
#include <boost/asio.hpp>
#include <thread>
#include <atomic>

namespace GameLib::Network::Base {

	class Server : public Interface::IServer {
	public:
		Server() : serverId_(Utils::generateUuid()) {}
		
		virtual ~Server() = default;

	protected:
		boost::asio::io_context ioContext_;
		std::thread ioThread_;
		Utils::uuid serverId_;
		std::atomic<bool> running_{false};
	
	
	};

}