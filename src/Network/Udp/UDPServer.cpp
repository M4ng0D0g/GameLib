#include "gamelib/network/UDPServer.hpp"
#include <thread>
#include <memory>
#include <iostream>

namespace GameLib::Network {

	UDPServer::UDPServer(unsigned short port)
		: socket_(ioContext_, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {}

	void UDPServer::start() {
		doReceive();
		ioThread_ = std::thread([this]() { ioContext_.run(); });
	}

	void UDPServer::stop() {
		ioContext_.stop();
		if (ioThread_.joinable())
			ioThread_.join();
	}

	void UDPServer::doReceive() {
		socket_.async_receive_from(
			boost::asio::buffer(buffer_), remoteEndpoint_,
			[this](boost::system::error_code ec, std::size_t bytes_recvd) {
				if (!ec && bytes_recvd > 0) {
					std::string msg(buffer_.data(), bytes_recvd);
					std::cout << "Received UDP: " << msg << " from " << remoteEndpoint_ << std::endl;
				}
				doReceive();
			});
	}


}
