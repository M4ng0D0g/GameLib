#pragma once

namespace gamelib::core::interface {

	class IEngine {
	public:
		virtual ~IEngine() = default;

		virtual void init() = 0;
		virtual void run() = 0;
		 virtual void shutdown() = 0;
	};
}