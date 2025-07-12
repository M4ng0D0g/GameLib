#include "gamelib/core/Game.hpp"
#include <ctime>
#include <thread>
#include <chrono>

namespace GameLib::Core {

	Game::Game() : SPT_(GameEnv::TPS) {}

	// State Machine for Step-Based
	void Game::setState(GameState::UPtr newState) {
		if (currentState_) currentState_->onExit(*this);
		currentState_ = std::move(newState);
		if (currentState_) currentState_->onEnter(*this);
	}

	// 可能要做 update(action)
	void Game::updateState() {
		if (currentState_) currentState_->onUpdate(*this);
	}

	/*
	TODO: 步進機制與即時機制
	步進如果搭配動畫需要做[允許操作]檢查
	及時機制需要作時間校正、分批處理機制or多執行序
	*/
	void Game::loop() {
		// initial setup
		// std::cin.tie(0);
		// std::ios::sync_with_stdio(0);
		// configure_terminal();

		// init state
		clock_t startTime, endTime;

		// Main loop
		while(running_) {
			startTime = clock();

			// GameFlow
			updateState();

			endTime = clock();

			// tick rate normalization
			double timeTaken = (static_cast<double>(endTime - startTime)) / CLOCKS_PER_SEC;
			if (timeTaken > SPT_) continue;
			int tickDelay = static_cast<int>((SPT_ - timeTaken) * 1000); // 0.1 seconds
			if (tickDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(tickDelay)); // tick delay
		}

		end();
	}
	
}

