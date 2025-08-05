#pragma once

#include "Game.hpp"
#include <memory>

namespace gamelib::game {

	class Game;

	class State {
	public:
		virtual ~State() = default;

		virtual void onEnter(Game& game) = 0;
		virtual void onUpdate(Game& game) = 0;
		virtual void onExit(Game& game) = 0;
	};

}

