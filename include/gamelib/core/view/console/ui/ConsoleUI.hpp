#pragma once

#include "gamelib/utils/Unit.hpp"
#include "gamelib/utils/AnsiPrint.hpp"
#include "gamelib/utils/Icon.hpp"
#include "BorderPatterns.h"
#include <vector>
#include <memory>

class BaseUI {
public:
	using Ptr = std::shared_ptr<BaseUI>;
	Ptr create(const Size2& pixel) {
		return Ptr(new BaseUI(pixel));
	}

protected:
	BaseUI(const Size2& pixel) : uiPixel_(pixel) {
		icon_ = Icon::create(pixel);
		borderEnable_ = false;
		priority_ = 0;
		display_ = true;
	}
	virtual ~BaseUI() = default;

	const Size2 uiPixel_;
	Size2 loc_;

	Icon::Ptr icon_;
	bool borderEnable_;
	UIBorder::Pattern borderPattern_;
	
	size_t priority_;
	bool display_;

public:
	const Icon::Ptr& getIcon() const { return icon_; }
	Icon::Ptr& getIconRef() { return icon_; }

	const Size2& getLoc() const { return loc_; }
	bool getBorderEnable() const { return borderEnable_; }
	UIBorder::Pattern getBorderPattern() const { return borderPattern_; }
	size_t getPriority() const { return priority_; }
	bool getDisplay() const { return display_; }

	void setLoc(Size2 loc) { loc_ = loc; }
	void setBorderEnable(bool b) { borderEnable_ = b; }
	void setBorderPattern(UIBorder::Pattern p) { borderPattern_ = p; }
	void setPriority(size_t p) { priority_ = p; }
	void setDisplay(bool b) { display_ = b; }
};