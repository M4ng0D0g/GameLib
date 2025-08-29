#pragma once
#include "gamelib/utils/AnsiPrint.hpp"
#include "gamelib/utils/Icon.hpp"
#include "gamelib/utils/Unit.hpp"
#include <memory>

namespace gamelib::graphics::console::ui {

	class Viewable {
	public:
		Viewable(const utils::Pos2<size_t>& size) : icon_(size) {}
		virtual ~Viewable() = default;
		virtual void render() = 0;

	protected:
		utils::Icon icon_;
		// bool borderEnable_ = false;
		// UIBorder::Pattern borderPattern_;
		bool display_ = true;
	};

	/*
	class Viewable {
	public:
		const Icon& Viewable::getIcon() const { return icon_; }
		virtual const Loc2& getLocation() const = 0;

		void Viewable::setIcon(const Icon& icon) { icon_ = icon; }
		virtual void setLocation(const Loc2&) = 0;
	};

	*/

	

}