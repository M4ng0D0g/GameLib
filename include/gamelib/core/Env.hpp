#pragma once

namespace gamelib::env {

	// connect/server
	static int SERVER_PORT;
	static int MAX_CLIENTS;

	// core/game
	static double GAME_TPS = 20; // tick(s) per second, 畫面與此同步更新

	// core/view/console
	// Window 的 size
	static GameLib::Utils::Size2 WINDOW_SIZE;
	static double WINDOW_FPS = 20;
}


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
