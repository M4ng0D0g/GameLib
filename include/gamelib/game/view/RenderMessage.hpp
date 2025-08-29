#pragma once

#include <nlohmann/json.hpp>

namespace gamelib::game::view {

	struct RenderMessage {
		nlohmann::json payload;
	};
	
}

