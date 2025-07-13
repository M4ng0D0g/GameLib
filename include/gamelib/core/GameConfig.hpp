#pragma once

// #include "utils/Unit.h"
#include <memory>

namespace GameLib::Core {

	struct GameConfig {
		GameConfig() = default;
	};

}

// class GameConfig {
// public:
// 	const Size2 fieldSize;

// 	// Window 的 size

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