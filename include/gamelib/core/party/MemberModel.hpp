#pragma once 

#include "gamelib/network/SessionModel.hpp"
#include "gamelib/utils/Unit.hpp"
#include <memory>

using namespace GameLib::Network;
using namespace GameLib::Utils::Unit;

namespace GameLib::Core::Party {

	class MemberModel {
	protected:
		static Token token_;

		SessionModel::S_Ptr session_;
		bool host_;
		bool operator_;
		bool online_;
	
	public:
		using S_Ptr = std::shared_ptr<MemberModel>;

		using Ptr = std::shared_ptr<ClientSession>;
		static Ptr create(Token token, ENetPeer* peer) {
			return Ptr(new ClientSession(token, peer));
		}
		
	};
}

/*
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
*/