#pragma once
#include "AnsiPrint.hpp"
#include "Unit.hpp"
#include <vector>
#include <memory>
#include <string>

namespace gamelib::utils {

	struct Cell {
		std::string text;
		utils::AnsiColor fg;
		utils::AnsiColor bg;

		bool empty() const {
			return text.empty() || text == " ";
		}
	};
	
	class Icon {
	public:
		Icon(const Pos2<size_t>& size) : size_(size) {
			data_ = std::vector<std::vector<Cell>>(size.row, std::vector<Cell>(size.col));
		}

		Pos2<size_t> getSize() const {
			return size_;
		}
		Cell get(int x, int y) const {
			return data_[y][x];
		}
		void set(int x, int y, const Cell& cell) {
			data_[y][x] = cell;
		}
	
	private:
		std::vector<std::vector<Cell>> data_;
		const Pos2<size_t> size_;
	};

	// class Icon {
	// public:
	// 	std::vector<std::vector<AnsiColor::Ptr>>& getColorRef() { return color_; }
	// 	const std::vector<std::vector<AnsiColor::Ptr>>& getColor() const { return color_; }

	// 	std::vector<std::vector<char>>& getAsciiRef() { return ascii_; }
	// 	const std::vector<std::vector<char>>& getAscii() const { return ascii_; }

	// private:
	// 	Icon(const utils::Pos2<size_t>& size) : size_(size) {
	// 		color_ = std::vector<std::vector<AnsiColor::Ptr>>(size.height, std::vector<AnsiColor::Ptr>(size.width));
	// 		ascii_ = std::vector<std::vector<char>>(size.height, std::vector<char>(size.width));
	// 	}

	// 	utils::Pos2<size_t> size_;
	// 	std::vector<std::vector<AnsiColor::Ptr>> color_;
	// 	std::vector<std::vector<char>> ascii_;
	// };

	
}


