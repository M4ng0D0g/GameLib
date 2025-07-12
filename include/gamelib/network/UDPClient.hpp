#pragma once

#include <boost/asio.hpp>
#include <iostream>

namespace GameLib::Network {

	class UDPClient {
	public:
		UDPClient(const std::string& host, unsigned short port)
			: ioContext_(), socket_(ioContext_) {
			remoteEndpoint_ = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host), port);
			socket_.open(boost::asio::ip::udp::v4());
		}

		void send(const std::string& message) {
			socket_.send_to(boost::asio::buffer(message), remoteEndpoint_);
		}

	private:
		boost::asio::io_context ioContext_;
		boost::asio::ip::udp::socket socket_;
		boost::asio::ip::udp::endpoint remoteEndpoint_;
	};

} // namespace GameLib::Network
