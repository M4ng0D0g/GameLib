#include "gamelib/network/TCPClient.hpp"
#include <iostream>

namespace GameLib::Network {

	TCPClient::TCPClient(const std::string& host, unsigned short port)
		: socket_(ioContext_), host_(host), port_(port) {}

	TCPClient::~TCPClient() {
		disconnect();
	}

	void TCPClient::connect() {
		try {
			boost::asio::ip::tcp::resolver resolver(ioContext_);
			auto endpoints = resolver.resolve(host_, std::to_string(port_));
			boost::asio::connect(socket_, endpoints);
			connected_ = true;
			std::cout << "Connected to server." << std::endl;

			ioThread_ = std::thread([this]() { ioContext_.run(); });

		} catch (const std::exception& e) {
			std::cerr << "Connection failed: " << e.what() << std::endl;
		}
	}

	void TCPClient::send(const std::string& message) {
		if (connected_) {
			boost::asio::write(socket_, boost::asio::buffer(message));
		}
	}

	void TCPClient::disconnect() {
		if (connected_) {
			socket_.close();
			ioContext_.stop();
			if (ioThread_.joinable())
				ioThread_.join();
			connected_ = false;
		}
	}

}
