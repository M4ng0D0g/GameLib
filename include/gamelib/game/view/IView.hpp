#pragma once

#include <memory>
#include "RenderMessage.hpp"

namespace gamelib::game::view {

	class IView {
	public:
		virtual ~IView() = default;
		virtual void update(const RenderMessage& msg) = 0;
		// virtual void render() const = 0;
	};
}

