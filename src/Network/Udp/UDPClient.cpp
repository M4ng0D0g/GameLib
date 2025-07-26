#include "gamelib/network/UDPClient.hpp"
#include <iostream>

namespace GameLib::Network {

	UDPClient::UDPClient(const std::string& host, unsigned short port)
		: ioContext_(), socket_(ioContext_) {
		remoteEndpoint_ = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host), port);
		socket_.open(boost::asio::ip::udp::v4());
	}

	void UDPClient::send(const std::string& message) {
		socket_.send_to(boost::asio::buffer(message), remoteEndpoint_);
	}

}
