#pragma once

#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <memory>

namespace GameLib::Network {

	class TCPServer {
	public:
		TCPServer(unsigned short port);
		~TCPServer();

		void start();
		void stop();

	private:
		void doAccept();

		boost::asio::io_context ioContext_;
		boost::asio::ip::tcp::acceptor acceptor_;
		std::thread ioThread_;
		bool running_ = false;
	};
}