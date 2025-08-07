#pragma once

#include "interface/IEngine.hpp"
#include <memory>

namespace gamelib::core {

	class HostEngine : public interface::IEngine {
		friend class EngineBuilder;
	public:
		
		void init() override {

		}

		void run() override {
			
		}

		void shutdown() override {
			
		}
		
	private:
		HostEngine() {}

		// party or game
		// graphics

	};
}