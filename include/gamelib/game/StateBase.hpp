#pragma once

#include "GameBase.hpp"
#include <memory>

namespace gamelib::game {

	class GameBase;

	class StateBase {
	public:
		virtual ~StateBase() = default;

		virtual void onEnter(GameBase& game) = 0;
		virtual void onUpdate(GameBase& game) = 0;
		virtual void onExit(GameBase& game) = 0;
	};

}

