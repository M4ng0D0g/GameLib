#pragma once

#include "Unit.h"
#include "AnsiPrint.h"
#include <vector>
#include <memory>

class Icon {
public:
	using Ptr = std::shared_ptr<Icon>;
	static Ptr create(const Size2& size) {
		return Ptr(new Icon(size));
	}

private:
	Icon(const Size2& size) : size_(size) {
		color_ = std::vector<std::vector<AnsiColor::Ptr>>(size.height, std::vector<AnsiColor::Ptr>(size.width));
		ascii_ = std::vector<std::vector<char>>(size.height, std::vector<char>(size.width));
	}

	Size2 size_;
	std::vector<std::vector<AnsiColor::Ptr>> color_;
	std::vector<std::vector<char>> ascii_;

public:
	size_t icon_width() const { return size_.width; }
	size_t icon_height() const { return size_.height; }

	std::vector<std::vector<AnsiColor::Ptr>>& getColorRef() { return color_; }
	const std::vector<std::vector<AnsiColor::Ptr>>& getColor() const { return color_; }

	std::vector<std::vector<char>>& getAsciiRef() { return ascii_; }
	const std::vector<std::vector<char>>& getAscii() const { return ascii_; }
};


/*
struct PieceModel {
    int type;
    int hp;
    int x, y;
};

struct RenderInfo {
    char ascii;
    std::vector<Color> colors;
};

std::unordered_map<int, RenderInfo> pieceRenderMap;

*/