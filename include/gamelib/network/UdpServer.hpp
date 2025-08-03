#pragma once

#include "GameLib/Network/Base/Server.hpp"
#include <boost/asio.hpp>
#include <memory>
#include <iostream>

namespace GameLib::Network {

	class UdpServer : public Base::Server {
	private:
		boost::asio::ip::udp::socket socket_;
		boost::asio::ip::udp::endpoint remoteEndpoint_;
		std::array<char, 1024> buffer_;

		void doReceive() {
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

	public:
		UdpServer(unsigned short port)
			: socket_(ioContext_, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {}

		void start() override {
			doReceive();
			ioThread_ = std::thread([this]() { ioContext_.run(); });
		}

		void stop() override {
			ioContext_.stop();
			if (ioThread_.joinable())
				ioThread_.join();
		}
	};
}