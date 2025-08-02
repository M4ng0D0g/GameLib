#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <sstream>
#include <string>
#include <iomanip>
#include <random>
#include <vector>

// ***************************************************************************/

namespace gamelib::utils {

	using uuid = std::string;

	// uuid generateV4() {
	// 	// 產生 16 個隨機位元組
	// 	std::vector<uint8_t> bytes(16);
		
	// 	std::random_device rd;
	// 	std::mt19937_64 gen(rd());
	// 	std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);
	// 	for(int i = 0; i < 16; i += 4) {
	// 		uint32_t v = dist(gen);
	// 		bytes[i+0] = (v >> 24) & 0xFF;
	// 		bytes[i+1] = (v >> 16) & 0xFF;
	// 		bytes[i+2] = (v >> 8) & 0xFF;
	// 		bytes[i+3] = (v) & 0xFF;
	// 	}

	// 	// 設定版本 (0100) 及變體 (10xxxxxx)
	// 	bytes[6] = (bytes[6] & 0x0F) | 0x40;  // version field → 4
	// 	bytes[8] = (bytes[8] & 0x3F) | 0x80;  // variant field → 10

	// 	// 格式化為 8-4-4-4-12
	// 	std::ostringstream oss;
	// 	oss << std::hex << std::setfill('0');
	// 	for(int i = 0; i < 16; ++i) {
	// 		oss << std::setw(2) << static_cast<int>(bytes[i]);
	// 		if (i==3 || i==5 || i==7 || i==9) oss << '-';
	// 	}
	// 	return oss.str();
	// }

	inline uuid generateUuid() {
		static boost::uuids::random_generator generator;
		return to_string(generator());
	}
}
