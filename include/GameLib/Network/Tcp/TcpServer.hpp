#pragma once

#include "GameLib/Network/Base/Server.hpp"
#include "TcpSessionManager.hpp"
#include <boost/asio.hpp>
#include <vector>
#include <memory>

namespace GameLib::Network::Tcp {

	class TcpServer : public Base::Server {
	private:
		boost::asio::ip::tcp::acceptor acceptor_;
		SessionManager::U_Ptr sessionManager_;

		void doAccept() {
			auto socket = std::make_shared<boost::asio::ip::tcp::socket>(ioContext_);
			acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec) {
				if (!ec) {
					std::cout << "Client connected from: " << socket->remote_endpoint() << std::endl;
					
					// Step 1: 接收第一筆資料（UUID）
					auto buffer = std::make_shared<std::vector<char>>(64); // 預期只會送一段 uuid
					socket->async_read_some(boost::asio::buffer(*buffer), 
						[this, socket, buffer](boost::system::error_code ec2, std::size_t length) {
							if (!ec2) {
								std::string uuid(buffer->begin(), buffer->begin() + length);
								trim(uuid); // 去掉換行符等（你可自己寫 trim）

								auto existing = sessionManager_->findById(uuid);
								if (existing) {
									std::cout << "Resuming session " << uuid << "\n";
									existing->resume(std::move(socket));
									existing->start();
								} else {
									auto session = sessionManager_->createSession(socket);
									std::cout << "Created new session: " << session->getId() << "\n";
									session->start();

									// TODO: 回傳新的 UUID 給 client（你可自定格式）
								}
							} else {
								std::cerr << "Error reading UUID from client: " << ec2.message() << std::endl;
							}
							/*
							std::string message = "UUID:" + session->getId() + "\n";
							boost::asio::async_write(*socket, boost::asio::buffer(message), [](auto, auto){});
							*/
						});
					}
				doAccept(); // Accept next
			});
		}

	public:
		TcpServer(unsigned short port)
			: acceptor_(ioContext_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

		~TcpServer() {
			stop();
		}

		void start() override {
			running_ = true;
			doAccept();
			ioThread_ = std::thread([this]() {
				ioContext_.run();
			});
		}
		void stop() override {
			if (running_) {
				ioContext_.stop();
				if (ioThread_.joinable())
					ioThread_.join();
				running_ = false;
			}
		}

	
	};

	inline void trim(std::string& s) {
		s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
	}
}