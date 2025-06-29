#pragma once

#include "utils/Icon.h"
#include <unordered_map>

namespace UIBorder {
	enum class Type {
		C_TOP_LEFT, C_TOP_RIGHT, C_BOTTOM_LEFT, C_BOTTOM_RIGHT,
		S_TOP, S_LEFT, S_RIGHT, S_BOTTOM,
		T_TOP, T_LEFT, T_RIGHT, T_BOTTOM,
		CROSS, EMPTY
	};

	enum class Pattern {
		SINGLETHIN, SINGLETHICK, DOUBLE
	};

	static const std::unordered_map<Type, Cell> SingleThin = {
		{ Type::C_TOP_LEFT, Cell('┌') },
		{ Type::C_TOP_RIGHT, Cell('┐') },
		{ Type::C_BOTTOM_LEFT, Cell('└') },
		{ Type::C_BOTTOM_RIGHT, Cell('┘') },
		{ Type::S_TOP, Cell('─') },
		{ Type::S_LEFT, Cell('│') },
		{ Type::S_RIGHT, Cell('│') },
		{ Type::S_BOTTOM, Cell('─') },
		{ Type::T_TOP, Cell('┬') },
		{ Type::T_LEFT, Cell('├') },
		{ Type::T_RIGHT, Cell('┤') },
		{ Type::T_BOTTOM, Cell('┴') },
		{ Type::CROSS, Cell('┼') },
		{ Type::EMPTY, Cell(' ') },
	};

	static const std::unordered_map<Type, Cell> SingleThick = {
		{ Type::C_TOP_LEFT, Cell('┏') },
		{ Type::C_TOP_RIGHT, Cell('┓') },
		{ Type::C_BOTTOM_LEFT, Cell('┗') },
		{ Type::C_BOTTOM_RIGHT, Cell('┛') },
		{ Type::S_TOP, Cell('━') },
		{ Type::S_LEFT, Cell('┃') },
		{ Type::S_RIGHT, Cell('┃') },
		{ Type::S_BOTTOM, Cell('━') },
		{ Type::T_TOP, Cell('┳') },
		{ Type::T_LEFT, Cell('┣') },
		{ Type::T_RIGHT, Cell('┫') },
		{ Type::T_BOTTOM, Cell('┻') },
		{ Type::CROSS, Cell('╋') },
		{ Type::EMPTY, Cell(' ') },
	};

	static const std::unordered_map<Type, Cell> Double = {
		{ Type::C_TOP_LEFT, Cell('╔') },
		{ Type::C_TOP_RIGHT, Cell('╗') },
		{ Type::C_BOTTOM_LEFT, Cell('╚') },
		{ Type::C_BOTTOM_RIGHT, Cell('╝') },
		{ Type::S_TOP, Cell('═') },
		{ Type::S_LEFT, Cell('║') },
		{ Type::S_RIGHT, Cell('║') },
		{ Type::S_BOTTOM, Cell('═') },
		{ Type::T_TOP, Cell('╦') },
		{ Type::T_LEFT, Cell('╠') },
		{ Type::T_RIGHT, Cell('╣') },
		{ Type::T_BOTTOM, Cell('╩') },
		{ Type::CROSS, Cell('╬') },
		{ Type::EMPTY, Cell(' ') },
	};
}


