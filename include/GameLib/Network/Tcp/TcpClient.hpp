#pragma once

#include <boost/asio.hpp>
#include <thread>
#include <string>

namespace GameLib::Network {

	class TCPClient {
	public:
		TCPClient(const std::string& host, unsigned short port);
		~TCPClient();

		void connect();
		void send(const std::string& message);
		void disconnect();

	private:
		boost::asio::io_context ioContext_;
		boost::asio::ip::tcp::socket socket_;
		std::string host_;
		unsigned short port_;
		std::thread ioThread_;
		bool connected_ = false;
	};

} // namespace GameLib::Network
