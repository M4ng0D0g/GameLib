#pragma once

#include <random>

namespace GameLib::Utils {

	struct RNG {
		std::mt19937 rng;

		RNG() : rng(std::random_device{}()) {}

		explicit RNG(size_t seedValue) : rng(seedValue) {}

		int random(int min = 0, int max = RAND_MAX) {
			std::uniform_int_distribution<int> dist(min, max);
			return dist(rng);
		}
	};
	
}

