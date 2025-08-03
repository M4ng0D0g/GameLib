#pragma once

#include "interface/IEngine.hpp"
#include "ClientEngine.hpp"
#include "ServerEngine.hpp"
#include "LocalEngine.hpp"
#include "gamelib/network/interface/IServer.hpp"
#include "gamelib/network/interface/IClient.hpp"
#include "gamelib/game/Game.hpp"
#include <memory>

namespace gamelib::core {

	enum class EngineType { Client, Local, Server }

	class EngineBuilder {
	public:

		EngineBuilder& setType(EngineType type) {
			type_ = type;
			return *this;
		}

		// --------------------------------------------------------------------------------

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

		EngineBuilder& withParty() {

		}

		EngineBuilder& withGame(std::shared_ptr<game::Game> game) {
			game_ = std::move(game);
			return *this;
		}

		// --------------------------------------------------------------------------------

		std::shared_ptr<interface::IEngine> build() {
			switch (type_) {
				case EngineType::Local:
					return std::shared_ptr<interface::IEngine>(new LocalEngine());

				case EngineType::Server:
					return std::shared_ptr<interface::IEngine>(new ServerEngine());

				case EngineType::Client:
					return std::shared_ptr<interface::IEngine>(new ClientEngine());
			}
		}
		
	private:
		EngineBuilder() {};
		EngineBuilder(const EngineBuilder&) = delete;
		EngineBuilder& operator=(const EngineBuilder&) = delete;

		static EngineBuilder& instance() {
			static EngineBuilder inst;
			return inst;
		}

		EngineType type_;
		std::shared_ptr<network::interface::IServer> server_{nullptr};
		std::shared_ptr<network::interface::IClient> client_{nullptr};
	};
}