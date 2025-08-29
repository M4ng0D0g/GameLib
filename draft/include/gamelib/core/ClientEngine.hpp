#pragma once

#include "interface/IEngine.hpp"
#include "gamelib/network/interface/IClient.hpp"
#include <memory>

namespace gamelib::core {

	// 分成2種設計模式
	// 1. 初始化時從Env獲取server host/port
	// 2. 若無法獲取，透過用戶輸入獲取
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