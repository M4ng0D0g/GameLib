#pragma once 

#include "gamelib/game/Game.hpp"
#include "gamelib/game/GameConfig.hpp"
#include "gamelib/session/interface/ISession.hpp"
#include <vector>
#include <unordered_map>
#include <string>

using SessionPtr = std::shared_ptr<gamelib::session::interface::ISession>;

namespace gamelib::party {

	using Token = uint32_t;

	class Party {
	public:
		void join();
		void leave();
		void clearDisconnectedMember();

		void ready();
		void unready();

		void launchGame();

	protected:
		Token partyId_;
		std::string partyName_;
		std::string partyPassword_; // Password is empty if not locked.

		std::vector<SessionPtr> members_; // int memberCnt_ = members_.size();

		// Components (ECS pattern)
		std::unordered_map<Token, bool> host_;
		// bool operator_;
		std::unordered_map<Token, bool> ready_;
		
		
		std::unique_ptr<game::Game> game_;
		std::shared_ptr<game::GameConfig> gameConfig_;
		// Developers can inheritance and add team system in gameConfig_.
		
	};
}