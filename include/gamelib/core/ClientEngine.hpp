#pragma once

#include "interface/IEngine.hpp"
#include "gamelib/network/interface/IClient.hpp"
#include <memory>

namespace gamelib::core {

	class ClientEngine : public interface::IEngine {
		friend class EngineBuilder;

	public:
		
		void init() override {

		}

		void run() override {

		}

		void shutdown() override {
			
		}
		
	private:
		ClientEngine() {}

		std::shared_ptr<network::interface::IClient> client_;
		// graphics

	};
}