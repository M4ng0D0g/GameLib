#pragma once
#include "gamelib/utils/Unit.hpp"
#include "gamelib/utils/AnsiPrint.hpp"
#include "UIIcon.hpp"
#include "UIBorder.hpp"
#include <memory>

namespace gamelib::graphics::console::ui {

	class UIViewable {
	public:
		virtual ~UIViewable() = default;

		bool isBorderEnable() const {
			return border_;
		}
		void setBorderEnable(bool b) {
			border_ = b;
		}

		// UIBorder::Pattern getBorderPattern() const {
		// 	return borderPattern_;
		// }
		// void setBorderPattern(UIBorder::Pattern p) {
		// 	borderPattern_ = p;
		// }
		
	protected:
		UIIcon icon_;
		bool border_ = false;
	};

}