#pragma once

#include <gamelib/Utils.hpp>

namespace gamelib::core::base {

	class EngineBase {
	public:
		virtual ~EngineBase() = default;

	protected:
		inline static utils::Logger& logger_ = utils::Logger::instance();
		
		bool initialized_{false};
		
	};
}