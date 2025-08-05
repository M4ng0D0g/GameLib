#pragma once

#include "interface/IEngine.hpp"
#include "gamelib/network/interface/IServer.hpp"
#include "gamelib/session/SessionManger.hpp"
#include <memory>
#include <gamelib/Event.hpp>
#include <gamelib/Utils.hpp>
#include <gamelib/Party.hpp>

namespace gamelib::core {

	class ServerEngine : public interface::IEngine {
		friend class EngineBuilder;

	public:
		
		void init() override {

		}

		void run() override {
			// 1. 啟動 Server
			if (!server_->start()) {
				logger_.error("Server failed to start.");
				return;
			}
			logger_.info("Server starts successfully.");

			// 2. 建立 SessionManager 管理 Session
			sessionManager_ = std::make_unique<session::SessionManager>();
			// SessionManager 是主動計時 + 被動管理
			// 應做一個自動計時函式
			sessionManager_->tick();
			

			// 3. 建立 PartyManager 管理 PartyMember 和 Game
			partyManager_ = std::make_unique<party::PartyManager>();

		}

		void shutdown() override {
			server_->stop();
		}
		
	private:
		ServerEngine() {}

		utils::Logger& logger_ = utils::Logger::instance();

		std::unique_ptr<network::interface::IServer> server_;
		std::unique_ptr<session::SessionManager> sessionManager_;
		std::unique_ptr<party::PartyManager> partyManager_;
		event::EventBus eventBus_;

	};
}