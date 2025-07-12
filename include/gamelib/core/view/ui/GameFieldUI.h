#pragma once

#include "BaseUI.h"
#include "utils/Unit.h"
#include <memory>

class GameFieldUI : public BaseUI {
public:
	using Ptr = std::shared_ptr<GameFieldUI>;
	Ptr create(const Size2& fs, const Size2& is = {1, 2}) {
		return Ptr(new GameFieldUI(fs, is));
	}

private:
	GameFieldUI(const Size2& fs, const Size2& is)
	: BaseUI(Size2{fs.width * is.width, fs.height * is.height}), fieldSize_(fs), iconSize_(is) {}

	const Size2 fieldSize_;
	const Size2 iconSize_;

public:

};