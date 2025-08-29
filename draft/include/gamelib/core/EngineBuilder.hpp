#pragma once

#include "ClientEngine.hpp"
#include "HostEngine.hpp"
#include "ServerEngine.hpp"
#include "StandaloneEngine.hpp"
#include "gamelib/game/interface/IGameManager.hpp"
#include "gamelib/network/interface/IServer.hpp"
#include "gamelib/network/interface/IClient.hpp"
#include "gamelib/party/PartyManager.hpp"
#include "gamelib/utils/Logger.hpp"
#include <memory>

using namespace gamelib::utils;

namespace gamelib::core {
	
	enum class BuildMode {
		Standalone, DedicatedServer, RemoteClient, Host
	};

	class EngineBuilder {
	public:
		EngineBuilder& withGame(std::unique_ptr<game::interface::IGameManager>&& gameMngr) {
			gameMngr_ = std::move(gameMngr);
			return *this;
		}

		// 完美建構傳輸
		// template <typename GameT, typename... Args>
		// EngineBuilder& withGame(Args&&... args) {
		// 	gameMngr_ = std::make_unique<game::GameManager<GameT>>(std::forward<Args>(args)...);
		// 	return *this;
		// }

		EngineBuilder& withServer(std::unique_ptr<network::interface::IServer>&& server) {
			server_ = std::move(server);
			return *this;
		}

		EngineBuilder& withClient(std::unique_ptr<network::interface::IClient>&& client) {
			client_ = std::move(client);
			return *this;
		}

		EngineBuilder& withParty(std::unique_ptr<party::PartyManager>&& partyMngr) {
			partyMngr_ = std::move(partyMngr);
			return *this;
		}

		// --------------------------------------------------------------------------------

		std::unique_ptr<interface::IEngine> build(BuildMode mode) {
			switch (mode) {
				case BuildMode::Standalone:
					if (!gameMngr_) throw std::logic_error("缺乏 .withGame()");
					// TODO: Graphics
					return std::make_unique<StandaloneEngine>();
					
				case BuildMode::DedicatedServer:
					if (!server_) throw std::logic_error("缺乏 .withServer()");
					if (!gameMngr_) throw std::logic_error("缺乏 .withGame()");
					// .withParty() 可選
					return std::make_unique<ServerEngine>();

				case BuildMode::RemoteClient:
					if (!client_) throw std::logic_error("缺乏 .withClient()");
					// TODO: Graphics
					return std::make_unique<ClientEngine>();

				case BuildMode::Host:
					if (!server_) throw std::logic_error("缺乏 .withServer()");
					if (!gameMngr_) throw std::logic_error("缺乏 .withGame()");
					// .withParty() 可選
					return std::make_unique<HostEngine>();

				default: return nullptr;
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

		Logger& logger = Logger::instance();

		// Game
		std::unique_ptr<game::interface::IGameManager> gameMngr_{nullptr};

		// Graphics

		// Network
		std::unique_ptr<network::interface::IServer> server_{nullptr};
		std::unique_ptr<network::interface::IClient> client_{nullptr};

		// Party
		std::unique_ptr<party::PartyManager> partyMngr_{nullptr};
	};
}