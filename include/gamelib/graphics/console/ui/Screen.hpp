#pragma once

#include "UIBase.hpp"
#include <memory>
#include <vector>

namespace gamelib::graphics::console::ui {

	class Screen {
	public:

		void render() {
			panelCur_->render();
		}	

	private:
		std::unique_ptr<UIBase> uiList_;
	};
}