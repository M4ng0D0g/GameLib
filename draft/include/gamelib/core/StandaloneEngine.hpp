#pragma once

#include "interface/IEngine.hpp"
#include <memory>

namespace gamelib::core {

	class StandaloneEngine : public interface::IEngine {
		friend class EngineBuilder;
	public:
		
		void init() override {

		}

		void run() override {
			
		}

		void shutdown() override {
			
		}
		
	private:
		StandaloneEngine() {}

		// party or game
		// graphics

	};
}