#pragma once

#include "utils/Unit.hpp"

namespace GameLib::Env {

	// connect/Server
	static int SERVER_PORT = 12345;
	static int MAX_CLIENTS = 10;

	// core/Game
	static double GAME_TPS = 20; // tick(s) per second, 畫面與此同步更新
}


// class Environment {
// private:
// 	Environment() {};
// 	~Environment() {};

// public:	
// 	Environment(const Environment&) = delete;
// 	Environment& operator=(const Environment&) = delete;
// 	static Environment& get() {
// 		static Environment instance;
// 		return instance;
// 	}

// 	// Window 的 size
// 	const Size2 WINDOW_SIZE;

// 	// Icon 的 Cell size
// 	const Size2 GAME_WINDOW_SCALE = {1, 5};
// 	const Size2 GAME_WINDOW = {
// 		fieldSize.width * GAME_WINDOW_SCALE.width,
// 		fieldSize.height * GAME_WINDOW_SCALE.height
// 	};

// 	// Cell 的 char size
// 	const Size2 GAME_WINDOW_CELL = {13, 1};
// 	const Size2 WINDOW_PIXEL = {
// 		GAME_WINDOW.width * GAME_WINDOW_CELL.width,
// 		GAME_WINDOW.height * GAME_WINDOW_CELL.height
// 	};
// 	const double SPF = 0.05;

// 	IGameConfig(const Size2& fs)
// 		: fieldSize(fs),
// 		GAME_WINDOW({
// 			fieldSize.width * GAME_WINDOW_SCALE.width,
// 			fieldSize.height * GAME_WINDOW_SCALE.height
// 		}),
// 		WINDOW_PIXEL({
// 			GAME_WINDOW.width * GAME_WINDOW_CELL.width,
// 			GAME_WINDOW.height * GAME_WINDOW_CELL.height
// 		}) {}


// };