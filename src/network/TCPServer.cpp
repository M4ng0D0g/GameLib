#include "gamelib/network/TCPServer.hpp"
#include <iostream>

namespace GameLib::Network {

	TCPServer::TCPServer(unsigned short port)
		: acceptor_(ioContext_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

	TCPServer::~TCPServer() {
		stop();
	}

	void TCPServer::start() {
		running_ = true;
		doAccept();
		ioThread_ = std::thread([this]() {
			ioContext_.run();
		});
	}

	void TCPServer::stop() {
		if (running_) {
			ioContext_.stop();
			if (ioThread_.joinable())
				ioThread_.join();
			running_ = false;
		}
	}

	void TCPServer::doAccept() {
		auto socket = std::make_shared<boost::asio::ip::tcp::socket>(ioContext_);
		acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec) {
			if (!ec) {
				std::cout << "Client connected from: " << socket->remote_endpoint() << std::endl;

				auto buffer = std::make_shared<std::vector<char>>(1024);
				socket->async_read_some(boost::asio::buffer(*buffer), [socket, buffer](boost::system::error_code ec, std::size_t length) {
					if (!ec) {
						std::string msg(buffer->begin(), buffer->begin() + length);
						std::cout << "Received: " << msg << std::endl;
					}
				});
			}
			doAccept(); // Accept next
		});
	}

}
