#pragma once

#include "ClientSession.h"
#include "utils/uuid.h"
#include "utils/time.h"
#include <unordered_map>
#include <atomic>


// ***************************************************************************/

class SessionManager {
private:
	Time::time timeToClean; //TODO
	std::atomic<ClientSession::Token> nextToken_{1};

	std::unordered_map<ClientSession::Token, ClientSession::Ptr> tokenSessions_;
	std::unordered_map<ENetPeer*, ClientSession::Ptr> peerSessions_;
	
public:
	ClientSession::Token create(ClientSession::Token token, ENetPeer* peer);
	//超過時間清理(用Time)
	void remove(ClientSession::Token token);
	void cleanCheck();
	//Peer斷線
	void disconnect(ENetPeer*);

	ClientSession::Ptr getSession(ClientSession::Token token) {
		if(tokenSessions_.contains(token)) return tokenSessions_[token];
		else return nullptr;
	}

	ClientSession::Ptr getSession(ENetPeer* peer) {
		if(peerSessions_.contains(peer)) return peerSessions_[peer];
		else return nullptr;
	}


	

};