#pragma once

#include "interface/IEngine.hpp"
#include "gamelib/network/interface/IServer.hpp"
#include "gamelib/session/SessionManger.hpp"
#include <memory>

namespace gamelib::core {

	class ServerEngine : public interface::IEngine {
		friend class EngineBuilder;

	public:
		
		void init() override {

		}

		void run() override {
			server_->start();
		}

		void shutdown() override {
			server_->stop();
		}
		
	private:
		ServerEngine() {}

		std::shared_ptr<network::interface::IServer> server_;
		session::SessionManager sessionManager_;

	};
}