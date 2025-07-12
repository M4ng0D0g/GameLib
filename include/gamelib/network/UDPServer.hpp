#pragma once

#include <boost/asio.hpp>
#include <thread>
#include <memory>
#include <iostream>

namespace GameLib::Network {

	class UDPServer {
	public:
		UDPServer(unsigned short port)
			: socket_(ioContext_, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {}

		void start() {
			doReceive();
			ioThread_ = std::thread([this]() { ioContext_.run(); });
		}

		void stop() {
			ioContext_.stop();
			if (ioThread_.joinable())
				ioThread_.join();
		}

	private:
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

		boost::asio::io_context ioContext_;
		boost::asio::ip::udp::socket socket_;
		boost::asio::ip::udp::endpoint remoteEndpoint_;
		std::array<char, 1024> buffer_;
		std::thread ioThread_;
	};

} // namespace GameLib::Network
