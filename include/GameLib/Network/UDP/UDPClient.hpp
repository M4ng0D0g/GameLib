#pragma once

#include <boost/asio.hpp>
#include <iostream>

namespace GameLib::Network {

	class UDPClient {
	public:
		UDPClient(const std::string& host, unsigned short port);

		void send(const std::string& message);

	private:
		boost::asio::io_context ioContext_;
		boost::asio::ip::udp::socket socket_;
		boost::asio::ip::udp::endpoint remoteEndpoint_;
	};

} // namespace GameLib::Network
