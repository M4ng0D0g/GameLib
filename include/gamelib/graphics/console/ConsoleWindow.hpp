#pragma once
#include "gamelib/graphics/IWindow.hpp"
#include "gamelib/utils/Terminal.hpp"
#include "ui/Screen.hpp"
#include "gamelib/utils/Unit.hpp"

namespace gamelib::graphics::console {

	class ConsoleWindow : public IWindow {
	public:
		ConsoleWindow(const utils::Pos2<size_t>& size) : size_(size) {
			std::setlocale(LC_ALL, "");
			// auto make_str_buf = [config] {
			// 	return std::vector<std::vector<std::string>>(
			// 		config.GAME_WINDOW.height, std::vector<std::string>(config.GAME_WINDOW.width, ""));
			// };
			// auto make_col_buf = [config] {
			// 	return std::vector<std::vector<AnsiColor::Ptr>>(
			// 		config.GAME_WINDOW.height, std::vector<AnsiColor::Ptr>(
			// 			config.GAME_WINDOW.width,
			// 			AnsiColor::Basic(9)
			// 		)
			// 	);
			// };

			// latest_map   = last_map   = make_str_buf();
			// latest_fg_color = last_fg_color = make_col_buf();
			// latest_bg_color = last_bg_color = make_col_buf();
			// resetLatest();
		}
		// 整合舊程式碼
		// 使用樹狀ui呈現
		void render() {
			screenCur_.render(size_);
		}

		void resize(const utils::Pos2<size_t>& size) {
			size_ = size;
			// ...
		}

	private:
		ui::Screen screenCur_;
		utils::Terminal terminal_;
		utils::Pos2<size_t> size_;
	};
}