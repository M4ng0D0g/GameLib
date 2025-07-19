#pragma once

#include "PacketBuilder.h"
#include "Packet.h"
#include "utils/time.h"
#include <enet/enet.h>
#include <string>
#include <stdint.h>
#include <memory>

// ***************************************************************************/

class ClientSession {
public:
	using Token = uint64_t;

	using Ptr = std::shared_ptr<ClientSession>;
	static Ptr create(Token token, ENetPeer* peer) {
		return Ptr(new ClientSession(token, peer));
	}

private:
	ClientSession(Token token, ENetPeer* peer) : token_(token), peer_(peer) {}

	Token token_;
	ENetPeer* peer_;
	bool isOnline_;
	Time::time offlineTime_; 

public:
	Token getToken() const noexcept { return token_; }
	ENetPeer* getPeer() const { return peer_; }
	void setPeer(ENetPeer* peer) { peer_ = peer; }

	void online() { isOnline_ = true; }
	void offline() { isOnline_ = false; offlineTime_ = Time::steadyNowMs(); }
	bool isOnline() { return isOnline_; }
	Time::time getOfflineTime() { return offlineTime_; }
};