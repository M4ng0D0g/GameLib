#pragma once

#include <boost/asio.hpp>
#include <thread>
#include <memory>
#include <iostream>

namespace GameLib::Network {

	class UDPServer {
	public:
		UDPServer(unsigned short port);

		void start();
		void stop();

	private:
		void doReceive();

		boost::asio::io_context ioContext_;
		boost::asio::ip::udp::socket socket_;
		boost::asio::ip::udp::endpoint remoteEndpoint_;
		std::array<char, 1024> buffer_;
		std::thread ioThread_;
	};

} // namespace GameLib::Network
