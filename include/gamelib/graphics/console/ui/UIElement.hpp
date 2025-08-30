#pragma once
#include "gamelib/utils/Unit.hpp"
#include "gamelib/utils/AnsiPrint.hpp"
#include <memory>

namespace gamelib::graphics::console::ui {

	class UIElement {
	public:
		UIElement() {}
		virtual ~UIElement() = default;
		virtual void render() = 0;

		utils::Pos2<int> getPos() const { 
			return pos_;
		}
		void setLoc(const utils::Pos2<int> pos) {
			pos_ = pos;
		}

		size_t getPriority() const {
			return priority_;
		}
		void setPriority(size_t p) {
			priority_ = p;
		}

		bool getDisplay() const {
			return display_;
		}
		void setDisplay(bool b) {
			display_ = b;
		}
		
	protected:
		utils::Pos2<int> pos_;
		utils::Pos2<size_t> size_;
		size_t priority_ = 0;
		bool display_ = true;
	};

}