#pragma once
#include "gamelib/utils/Unit.hpp"
#include "gamelib/utils/AnsiPrint.hpp"
#include <memory>

namespace gamelib::graphics::console::ui {

	class UIElement {
	public:
		UIElement() {}
		virtual ~UIElement() = default;
		
	protected:
		utils::Pos2<size_t> pos_;
		utils::Pos2<size_t> size_;
		std::unique_ptr<utils::AnsiColor> fg_;
		std::unique_ptr<utils::AnsiColor> bg_;
		size_t priority_ = 0;
		bool enable_ = true;
	};

}