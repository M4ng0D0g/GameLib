#pragma once

#include "GameLib/Network/Base/Client.hpp"
#include "GameLib/Utils/Logger.hpp"
#include <boost/asio.hpp>

namespace GameLib::Network::Tcp {

	using namespace Utils;

	class TcpClient : public Base::Client {
	private:
		boost::asio::ip::tcp::socket socket_;
		std::string host_;
		unsigned short port_;

	public:
		TcpClient(const std::string& host, unsigned short port)
			: socket_(ioContext_), host_(host), port_(port) {}

		~TcpClient() {
			disconnect();
		}

		void connect() {
			Logger& logger = Logger::instance();
			if (connected_) {
				logger.error("Client has already connected.");
				return;
			}

			try {
				boost::asio::ip::tcp::resolver resolver(ioContext_);
				auto endpoints = resolver.resolve(host_, std::to_string(port_));
				boost::asio::connect(socket_, endpoints);
				connected_.store(true);
				logger.info("Connected to server.");

				ioThread_ = std::thread([this]() { ioContext_.run(); });

			} catch (const std::exception& e) {
				logger.error("Connection failed: " + std::string(e.what()));
			}
		}

		void disconnect() {
			Logger& logger = Logger::instance();
			if (!connected_) {
				logger.error("Client has already disconnected.");
				return;
			}

			socket_.close();
			ioContext_.stop();

			if (ioThread_.joinable()) ioThread_.join();
			connected_.store(false);
		}

		void send(const std::string& message) override {
			Logger& logger = Logger::instance();
			if (!connected_) {
				logger.error("Client hasn't connected to any server yet.");
				return;
			}

			boost::asio::write(socket_, boost::asio::buffer(message));
		}
		

	};
}
