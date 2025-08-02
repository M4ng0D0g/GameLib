#pragma once

#include "gamelib/network/interface/IServer.hpp"
#include <memory>

namespace gamelib::core {

	class Engine {
	public:

		Engine& withNetwork(std::shared_ptr<network::interface::IServer> server) {

		}

		Engine& withParty() {

		}

		Engine& withGame() {

		}

		// --------------------------------------------------------------------------------

		void init() {

		}

		void run() {

		}

		void shutdown() {
			
		}
	
	private:

	};
}