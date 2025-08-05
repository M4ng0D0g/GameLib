#pragma once

#include "interface/IEngine.hpp"
#include "ClientEngine.hpp"
#include "ServerEngine.hpp"
#include "LocalEngine.hpp"
#include "gamelib/network/interface/IServer.hpp"
#include "gamelib/network/interface/IClient.hpp"
#include <memory>

namespace gamelib::core {

	class EngineBuilder {
	public:
		EngineBuilder& withNetwork(std::shared_ptr<network::interface::IServer> server) {
			server_ = std::move(server);
			client_ = nullptr;
			return *this;
		}

		EngineBuilder& withNetwork(std::shared_ptr<network::interface::IClient> client) {
			client_ = std::move(client);
			server_ = nullptr;
			return *this;
		}

		// EngineBuilder& withParty() {
		// }

		// EngineBuilder& withGame(std::shared_ptr<game::Game> game) {
		// 	game_ = std::move(game);
		// 	return *this;
		// }

		// --------------------------------------------------------------------------------

		std::shared_ptr<interface::IEngine> build() {
			std::shared_ptr<interface::IEngine> engine = nullptr;

			if (server_ != nullptr) {
				engine = std::shared_ptr<interface::IEngine>(new ServerEngine());
			}
			else if (client_ != nullptr) {
				engine = std::shared_ptr<interface::IEngine>(new ClientEngine());

			}
			else {
				engine = std::shared_ptr<interface::IEngine>(new LocalEngine());

			}

			return engine;
		}
		
	private:
		EngineBuilder() {};
		EngineBuilder(const EngineBuilder&) = delete;
		EngineBuilder& operator=(const EngineBuilder&) = delete;

		static EngineBuilder& instance() {
			static EngineBuilder inst;
			return inst;
		}

		std::shared_ptr<network::interface::IServer> server_{nullptr};
		std::shared_ptr<network::interface::IClient> client_{nullptr};
	};
}