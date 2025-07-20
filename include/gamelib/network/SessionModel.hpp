#pragma once

#include "Message.hpp"
#include "gamelib/utils/Unit.hpp"
#include "gamelib/utils/Time.hpp"
#include <memory>
#include <functional>
#include <queue>
#include <mutex>

using namespace GameLib::Utils;

namespace GameLib::Network {

	class SessionModel : public std::enable_shared_from_this<SessionModel> {
	private:
		static Unit::Token curSessionId_;
		SessionModel(Unit::Token token, ENetPeer* peer) : sessionId_(token), peer_(peer);

		Unit::Token sessionId_;
		ENetPeer* peer_;
		bool connected_;
		Time::Time offlineTime_; 

		std::queue<Message::S_Ptr> recvQueue_;
		std::mutex queueMutex_;
		std::function<void(int)> handler_;

		Message::S_Ptr dequeueRecv();

	public:
		using S_Ptr = std::shared_ptr<SessionModel>;
		static S_Ptr create(Unit::Token token, ENetPeer* peer) {
			return S_Ptr(new SessionModel(token, peer));
		}

		explicit SessionModel(int sessionId);
		~SessionModel();

		int getSessionId() const;
		void onMessageRecived(Message::S_Ptr msg);
		void sendMessage(Message::S_Ptr msg);
		void setDisconnectHandler(std::function<void(int)> handler);
		void start();
		void stop();

		void online() { isOnline_ = true; }
		void offline() { isOnline_ = false; offlineTime_ = Time::steadyNowMs(); }
		bool isOnline() { return isOnline_; }
		Time::time getOfflineTime() { return offlineTime_; }
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

	class Session : public std::enable_shared_from_this<Session> {
	public:
		Session(tcp::socket socket) : socket_(std::move(socket)) {}

		void start() {
			do_read();
		}

	private:
		void do_read() {
			auto self = shared_from_this();
			socket_.async_read_some(
				boost::asio::buffer(data_),
				[self](boost::system::error_code ec, std::size_t length) {
					if (!ec) {
						// 處理資料
					}
				}
			);
		}

		tcp::socket socket_;
		char data_[1024];
	};
	*/

}