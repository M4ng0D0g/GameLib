#pragma once

#include "Game.hpp"
#include <memory>


namespace GameLib::Core::Game {

	class Game;

	class GameState {
	public:
		using U_Ptr = std::unique_ptr<GameState>;

		virtual ~GameState() = default;

		virtual void onEnter(Game& game) = 0;
		virtual void onUpdate(Game& game) = 0;
		virtual void onExit(Game& game) = 0;
	};

}

