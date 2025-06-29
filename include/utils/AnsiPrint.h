#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <sstream>

enum class AnsiMode {
	Basic,
	Bright,
	Color256,
	RGB
};

struct AnsiColor {
	using Ptr = std::shared_ptr<AnsiColor>;
	AnsiMode mode;
	int value;
	int r, g, b;

	static Ptr Basic(int v) { return Ptr(new AnsiColor{AnsiMode::Basic, v, 0, 0, 0}); }
	static Ptr Bright(int v) { return Ptr(new AnsiColor{AnsiMode::Bright, v, 0, 0, 0}); }
	static Ptr Color256(int v) { return Ptr(new AnsiColor{AnsiMode::Color256, v, 0, 0, 0}); }
	static Ptr RGB(int r, int g, int b) { return Ptr(new AnsiColor{AnsiMode::RGB, 0, r, g, b}); }
};

std::string ToAnsiCode(const AnsiColor::Ptr color, bool isForeground) {
	std::ostringstream oss;
	switch (color->mode) {
		case AnsiMode::Basic:
			oss << "\033[" << (isForeground ? 30 : 40) + color->value << "m";
			break;
		case AnsiMode::Bright:
			oss << "\033[" << (isForeground ? 90 : 100) + color->value << "m";
			break;
		case AnsiMode::Color256:
			oss << "\033[" << (isForeground ? 38 : 48) << ";5;" << color->value << "m";
			break;
		case AnsiMode::RGB:
			oss << "\033[" << (isForeground ? 38 : 48)
				<< ";2;" << color->r << ";" << color->g << ";" << color->b << "m";
			break;
	}
	return oss.str();
}

std::string AnsiPrint(
	const std::string& text,
	const AnsiColor::Ptr fg,
	const AnsiColor::Ptr bg,
	bool hi,
	bool blink
) {
	#ifndef _WIN
		std::ostringstream oss;
		oss << "\033[";

		if(hi) oss << "1;";
		if(blink) oss << "5;";

		std::string prefix = oss.str();
		if(!prefix.empty() && prefix.back() == ';') prefix.pop_back();
		if(prefix != "\033[") prefix += "m";

		std::string colorStr;
		if(fg) colorStr += ToAnsiCode(fg, true);
		if(bg) colorStr += ToAnsiCode(bg, false);

		return prefix + colorStr + text + "\033[0m";
	#else
		return text;
	#endif
}