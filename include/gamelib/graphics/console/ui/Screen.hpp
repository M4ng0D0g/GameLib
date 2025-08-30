#pragma once
#include "UIElement.hpp"
#include "gamelib/utils/Unit.hpp"
#include <memory>
#include <vector>

namespace gamelib::graphics::console::ui {

	class Screen {
	public:

		void render(const utils::Pos2<size_t>& size) {
			

			// panelCur_->render();
		}	

	private:
		std::unique_ptr<UIElement> uiList_;
	};
}