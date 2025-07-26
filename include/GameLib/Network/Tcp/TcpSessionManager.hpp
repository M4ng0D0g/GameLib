#pragma once

#include "Session.hpp"
#include "gamelib/utils/Uuid.hpp"
#include "gamelib/utils/Time.hpp"
#include <atomic>
#include <memory>
#include <unordered_map>

using namespace GameLib::Utils;

// ***************************************************************************/

namespace GameLib::Network {

	class SessionManager {
	private:
		static Uuid::uuid curManagerId_;

		// Time::Time timeToClean_; //TODO
		// std::atomic<Session::Token> nextToken_{1};

		std::unordered_map<Uuid::uuid, Session::S_Ptr> sessions_;
		// std::unordered_map<ENetPeer*, Session::Ptr> peerSessions_;
		
	public:
		using U_Ptr = std::unique_ptr<SessionManager>;

		Session::S_Ptr findById(const Uuid::uuid& uuid);
		Session::S_Ptr SessionManager::createSession(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
		void registerSession(const Uuid::uuid& uuid, Session::S_Ptr session);


		// Session::Token create(Session::Token token, ENetPeer* peer);

		// //超過時間清理(用Time)
		// void remove(Session::Token token);
		// void cleanCheck();
		// //Peer斷線
		// void disconnect(ENetPeer*);

		// Session::Ptr getSession(Session::Token token) {
		// 	if(tokenSessions_.contains(token)) return tokenSessions_[token];
		// 	else return nullptr;
		// }

		// Session::Ptr getSession(ENetPeer* peer) {
		// 	if(peerSessions_.contains(peer)) return peerSessions_[peer];
		// 	else return nullptr;
		// }

	};
}

