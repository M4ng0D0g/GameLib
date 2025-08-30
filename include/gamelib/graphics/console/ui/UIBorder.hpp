#pragma once
#include "gamelib/utils/Unit.hpp"
#include "gamelib/utils/AnsiPrint.hpp"
#include "UIIcon.hpp"
#include <memory>
#include <bitset>

namespace gamelib::graphics::console::ui {

	class UIBorder : public UICell {
	public:
		enum class Pattern {
			SINGLETHIN, SINGLETHICK, DOUBLE
		};
		enum Direction {
			UP = 0, DOWN, LEFT, RIGHT, COUNT
		};

		// OR（聯集）
		UIBorder operator|(const UIBorder& other) const {
			UIBorder newInst;
			newInst.dirs_ = (dirs_ | other.dirs_);
			return newInst;
		}
		UIBorder& operator|=(const UIBorder& other) {
			dirs_ |= other.dirs_;
			return *this;
		}
		// AND（交集）
		UIBorder operator&(const UIBorder& other) const {
			UIBorder newInst;
			newInst.dirs_ = dirs_ & other.dirs_;
			return newInst;
		}
		UIBorder& operator&=(const UIBorder& other) {
			dirs_ &= other.dirs_;
			return *this;
		}
		// XOR（差集）
		UIBorder operator^(const UIBorder& other) const {
			UIBorder newInst;
			newInst.dirs_ = dirs_ ^ other.dirs_;
			return newInst;
		}
		UIBorder& operator^=(const UIBorder& other) {
			dirs_ ^= other.dirs_;
			return *this;
		}

		Pattern getPattern() const {
			return pattern_;
		}
		void setPattern(Pattern p) {
			pattern_ = p;
		}
		bool getDirection(Direction dir) const {
			if (dir >= Direction::COUNT) return false;
			return dirs_[dir];
		}
		void setDirection(Direction dir, bool enable) {
			if (dir >= Direction::COUNT) return;
			dirs_[dir] = enable;
		}

		void buildText() {
			static const std::array<char, 16> SingleThin = {
				' ', '─', '─', '─', '│', '┌', '└', '├', '│', '┐', '┘', '┤', '│', '┬', '┴', '┼'
			};
			static const std::array<char, 16> SingleThick = {
				' ', '━', '━', '━', '┃', '┏', '┗', '┣', '┃', '┓', '┛', '┫', '┃', '┳', '┻', '╋'
			};
			static const std::array<char, 16> Double = {
				' ', '═', '═', '═', '║', '╔', '╚', '╠', '║', '╗', '╝', '╣', '║', '╦', '╩', '╬'
			};

			int idx = static_cast<int>(dirs_.to_ulong());
			switch (pattern_) {
				case Pattern::SINGLETHIN:  text = SingleThin[idx];  break;
				case Pattern::SINGLETHICK: text = SingleThick[idx]; break;
				case Pattern::DOUBLE:      text = Double[idx];      break;
				default: break;
			}
		}

	private:
		Pattern pattern_ = Pattern::SINGLETHIN;
		std::bitset<Direction::COUNT> dirs_{};
	};
}
