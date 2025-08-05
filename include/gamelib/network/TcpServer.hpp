#pragma once

#include "base/BaseConnection.hpp"
#include "interface/IServer.hpp"
#include <gamelib/Utils.hpp>
#include <vector>
#include <memory>

namespace gamelib::network {

	class TcpServer
		: public interface::IServer, public base::BaseConnection {
	public:
		TcpServer(unsigned short port)
			: acceptor_(ioContext_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
			BaseConnection(utils::generateUuid()) {}

		~TcpServer() {
			stop();
		}

		// --------------------------------------------------------------------------------

		bool start() override {
			running_ = true;
			doAccept();
			ioThread_ = std::thread([this]() {
				ioContext_.run();
			});

			return true;
		}

		void stop() override {
			if (running_) {
				ioContext_.stop();
				if (ioThread_.joinable())
					ioThread_.join();
				running_ = false;
			}
		}

	private:
		boost::asio::ip::tcp::acceptor acceptor_;

		void doAccept() {
			using boost::asio::ip::tcp;

			auto socket = std::make_shared<tcp::socket>(ioContext_);
			acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code& ec) {

				boost::asio::post(acceptor_.get_executor(), [this]{ doAccept(); });
				if (ec) return;

				try {
					// 有些平台 remote_endpoint() 可能丟例外，避免中斷流程
					std::cout << "Client connected from: " << socket->remote_endpoint() << std::endl;
				} catch (std::exception e) {
					std::cerr << e.what() << std::endl;
				}

				// Step 1: 接收第一筆資料（UUID）
				auto buffer = std::make_shared<boost::asio::streambuf>();
				boost::asio::async_read_until(*socket, *buffer, '\n',
					[this, socket, buffer](const boost::system::error_code& ec2, std::size_t bytes) {
						if (ec2) {
							std::cerr << "Error reading UUID from client: " << ec2.message() << std::endl;
							return;
						}

						std::istream is(buffer.get());
						std::string uuid_line;
						std::getline(is, uuid_line);
						trim(uuid_line);

						if (auto existing = sessionManager_->findTyped(uuid_line)) {
							std::cout << "Resuming session " << uuid_line << "\n";
							existing->resume(std::move(socket));
							existing->start();
						} else {
							auto session = sessionManager_->createSession(socket);
							std::cout << "Created new session: " << session->id() << "\n";
							session->start();

							// （可選）回傳新 UUID
							// std::string msg = "UUID:" + session->getId() + "\n";
							// boost::asio::async_write(*socket, boost::asio::buffer(msg), [](auto, auto){});
						}
						/*
						std::string message = "UUID:" + session->getId() + "\n";
						boost::asio::async_write(*socket, boost::asio::buffer(message), [](auto, auto){});
						*/
					});
			});
		}

	

	
	};

	inline void trim(std::string& s) {
		s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
		// auto not_sp = [](unsigned char ch){ return !std::isspace(ch); };
		// s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_sp));
		// s.erase(std::find_if(s.rbegin(), s.rend(), not_sp).base(), s.end());
	}
}