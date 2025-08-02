#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <sstream>

namespace gamelib::utils {

	enum class AnsiMode { BASIC, BRIGHT, COLOR256, RGB };
	enum Color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, GRAY, NOCHANGE};

	struct AnsiColor {
		AnsiMode mode;
		int value;
		int r, g, b;

		static std::shared_ptr<AnsiColor> Basic(Color v) {
			return std::shared_ptr<AnsiColor>(new AnsiColor{AnsiMode::BASIC, v, 0, 0, 0});
		}
		static std::shared_ptr<AnsiColor> Bright(Color v) {
			return std::shared_ptr<AnsiColor>(new AnsiColor{AnsiMode::BRIGHT, v, 0, 0, 0});
		}
		static std::shared_ptr<AnsiColor> Color256(Color v) {
			return std::shared_ptr<AnsiColor>(new AnsiColor{AnsiMode::COLOR256, v, 0, 0, 0});
		}
		static std::shared_ptr<AnsiColor> RGB(int r, int g, int b) {
			return std::shared_ptr<AnsiColor>(new AnsiColor{AnsiMode::RGB, 0, r, g, b});
		}
	};

	std::string ToAnsiCode(const std::shared_ptr<AnsiColor> color, bool isForeground) {
		std::ostringstream oss;
		switch (color->mode) {
			case AnsiMode::BASIC:
				oss << "\033[" << (isForeground ? 30 : 40) + color->value << "m";
				break;
			case AnsiMode::BRIGHT:
				oss << "\033[" << (isForeground ? 90 : 100) + color->value << "m";
				break;
			case AnsiMode::COLOR256:
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
		const std::shared_ptr<AnsiColor> fg,
		const std::shared_ptr<AnsiColor> bg,
		bool hi,
		bool blink
	) {
		#ifndef _WIN
			std::ostringstream oss;
			oss << "\033[";

			if (hi) oss << "1;";
			if (blink) oss << "5;";

			std::string prefix = oss.str();
			if (!prefix.empty() && prefix.back() == ';') prefix.pop_back();
			if (prefix != "\033[") prefix += "m";

			std::string colorStr;
			if (fg) colorStr += ToAnsiCode(fg, true);
			if (bg) colorStr += ToAnsiCode(bg, false);

			return prefix + colorStr + text + "\033[0m";
		#else
			return text;
		#endif
	}
}



