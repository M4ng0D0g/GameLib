#pragma once

#include "base/BaseSession.hpp"
#include "interface/ISession.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>

using namespace gamelib::utils;

namespace gamelib::session {

	class TcpPlayerSession :
		public base::BaseSession,
		public interface::ISession,
		public std::enable_shared_from_this<TcpPlayerSession>
		{
	public:
	
		static std::shared_ptr<TcpPlayerSession> create(
			const uuid& id, std::shared_ptr<boost::asio::ip::tcp::socket> socket
		) {
			static Token curToken = 0;
			return std::shared_ptr<TcpPlayerSession>(
				new TcpPlayerSession(++curToken, id, std::move(socket))
			);
		}

		~TcpPlayerSession() noexcept override = default;

		// --------------------------------------------------------------------------------

		void start() override {
			doRead();
		}
		void resume(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
			socket_ = socket;
		}
		void close() override {

		}
		void send(const network::Message& msg) override {

		}

		const std::chrono::_V2::steady_clock::time_point lastActive() override {

		}
		// std::string getRemoteIP() const;
		// uint16_t getRemotePort() const;

		// int getSessionId() const;
		// void onMessageRecived(Message::S_Ptr msg);
		// void sendMessage(Message::S_Ptr msg);
		// void setDisconnectHandler(std::function<void(int)> handler);

		// void online() { isOnline_ = true; }
		// void offline() { isOnline_ = false; offlineTime_ = Time::steadyNowMs(); }
		// bool isOnline() { return isOnline_; }
		// Time::time getOfflineTime() { return offlineTime_; }

	private:
		explicit TcpPlayerSession(
			Token token,
			const uuid& id,
			std::shared_ptr<boost::asio::ip::tcp::socket> socket
		) : BaseSession(token, id), socket_(std::move(socket)), buffer_(1024) {}

		
		// ENetPeer* peer_;
		// bool connected_;
		// Time::Time offlineTime_; 

		// std::queue<Message::S_Ptr> recvQueue_;
		// std::mutex queueMutex_;
		// std::function<void(int)> handler_;

		// Message::S_Ptr dequeueRecv();

		std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
		std::vector<char> buffer_;
		// auto endpoint = socket_.remote_endpoint();
		// auto ip = endpoint.address().to_string();  // "192.168.0.1"
		// auto port = endpoint.port();               // e.g., 52011
		// auto local = socket_.local_endpoint();
		// std::string sessionId = Uuid::generate(); // 或 auto-increment 編號
		// std::vector<uint8_t> recvBuffer;
		// std::deque<std::vector<uint8_t>> sendQueue;

		void doRead() override {
			auto self = shared_from_this();
			socket_->async_read_some(boost::asio::buffer(buffer_), [self](boost::system::error_code ec, std::size_t length) {
				if (!ec) {
					std::string msg(self->buffer_.begin(), self->buffer_.begin() + length);
					std::cout << "Received from " << self->socket_->remote_endpoint() << ": " << msg << std::endl;
					self->doRead(); // 持續讀取
				}
			});
		}
		void doWrite() override {
			
		}
	};

	/*
	#include <unordered_map>

	class Core {
	public:
		void addSession(ClientSessionModel::Ptr session);
		void removeSession(int sessionId);

		// 輪詢所有 session 的訊息並處理
		void update();

	private:
		std::unordered_map<int, ClientSessionModel::Ptr> sessions_;
	};

	*/

	/*
	acceptor.async_accept(socket, handler);
	或
	tcp::socket socket(io_context);
	acceptor.accept(socket); // 同步

	tcp::endpoint remote_ep = socket.remote_endpoint();
	std::cout << "Client connected from: " 
			<< remote_ep.address().to_string()
			<< ":" << remote_ep.port() << std::endl;
	也可以看自己 listener（本地）端口：

	tcp::endpoint local_ep = socket.local_endpoint();

	void do_accept() {
		acceptor.async_accept(
			[this](boost::system::error_code ec, tcp::socket socket) {
				if (!ec) {
					std::cout << "New client from "
							<< socket.remote_endpoint().address().to_string()
							<< "\n";

					// 將 socket 移交給某個 Session 類別處理
					std::make_shared<Session>(std::move(socket))->start();
				}
				do_accept(); // 等待下一個 client
			}
		);
	}
	*/

}