#pragma once

#include "interface/IEngine.hpp"
#include "gamelib/network/interface/IServer.hpp"
#include <memory>

namespace gamelib::core {

	class ServerEngine : public interface::IEngine {
		friend class EngineBuilder;

	public:
		
		void init() override {

		}

		void run() override {

		}

		void shutdown() override {
			
		}
		
	private:
		ServerEngine() {}

		std::shared_ptr<network::interface::IServer> server_;

	};
}