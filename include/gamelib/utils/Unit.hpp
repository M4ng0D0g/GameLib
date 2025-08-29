#pragma once
#include <iostream>
#include <concepts>
#include <type_traits>
#include <vector>

// ***************************************************************************/

namespace gamelib::utils {

	template <std::integral T>
	struct Pos2 {
		T x;
		T y;

		T& row = y;
		T& col = x;

		T& hor = x;
		T& ver = y;
		
		T& width = x;
		T& height = y;
	};
	
}