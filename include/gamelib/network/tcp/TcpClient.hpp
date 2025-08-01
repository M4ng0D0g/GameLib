#pragma once

#include "gamelib/network/base/BaseConnection.hpp"
#include "gamelib/network/interface/IClient.hpp"
#include "gamelib/utils/Logger.hpp"
#include <atomic>

using Logger = gamelib::utils::Logger;

namespace gamelib::network::tcp {

	class TcpClient : public interface::IClient, public base::BaseConnection {
	public:

		TcpClient(const std::string& host, unsigned short port)
			: socket_(ioContext_), host_(host), port_(port), BaseConnection(utils::generateUuid()) {}

		~TcpClient() {
			disconnect();
		}

		// --------------------------------------------------------------------------------

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

		// --------------------------------------------------------------------------------

		void send(const std::string& message) override {
			Logger& logger = Logger::instance();
			if (!connected_) {
				logger.error("Client hasn't connected to any server yet.");
				return;
			}

			boost::asio::write(socket_, boost::asio::buffer(message));
		}

	private:
		boost::asio::ip::tcp::socket socket_;
		std::string host_;
		unsigned short port_;

		std::atomic<bool> connected_;


	};
}
