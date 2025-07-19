#pragma once

#include "Message.hpp"
#include <memory>
#include <functional>
#include <queue>
#include <mutex>

namespace GameLib::Network {

	class SessionModel : public std::enable_shared_from_this<SessionModel> {
	private:
		int sessionId_;
		bool connected_;

		std::queue<Message::S_Ptr> recvQueue_;
		std::mutex queueMutex_;
		std::function<void(int)> handler_;

		Message::S_Ptr dequeueRecv();

	public:
		using S_Ptr = std::shared_ptr<SessionModel>;

		explicit SessionModel(int sessionId);
		~SessionModel();

		int getSessionId() const;
		void onMessageRecived(Message::S_Ptr msg);
		void sendMessage(Message::S_Ptr msg);
		void setDisconnectHandler(std::function<void(int)> handler);
		void start();
		void stop();
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

}