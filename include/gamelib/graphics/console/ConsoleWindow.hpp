#pragma once

#include "gamelib/graphics/IWindow.hpp"
#include "gamelib/utils/Terminal.hpp"

namespace gamelib::graphics::console {

	class ConsoleWindow : public IWindow {
	public:
		// 整合舊程式碼
		// 使用樹狀ui呈現
	private:
		utils::Terminal terminal_;
	};
}