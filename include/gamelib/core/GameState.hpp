#pragma once

#include "Game.hpp"
#include <memory>

class Game;

class GameState {
public:
	using UPtr = std::unique_ptr<GameState>;

public:
	virtual ~GameState() = default;

	virtual void onEnter(Game& game) = 0;
	virtual void onUpdate(Game& game) = 0;
	virtual void onExit(Game& game) = 0;
};