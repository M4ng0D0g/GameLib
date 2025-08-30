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

		T& row() { return y; }
		T& col() { return x; }
		const T& row() const { return y; }
		const T& col() const { return x; }

		T& hor() { return x; }
		T& ver() { return y; }
		const T& hor() const { return x; }
		const T& ver() const { return y; }

		T& width() { return x; }
		T& height() { return y; }
		const T& width() const { return x; }
		const T& height() const { return y; }
	};
	
}