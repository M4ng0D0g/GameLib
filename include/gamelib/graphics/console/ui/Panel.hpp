#pragma once

#include "UIElement.hpp"
#include <memory>
#include <unordered_map>

namespace gamelib::graphics::console::ui {

	class Panel : public UIElement {
	public:
		void render() override {
			if (!display_) return;

			// panelCur_->render();
		}	
		

	private:
		
		
	};
	
}