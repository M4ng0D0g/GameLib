#include "gamelib/core/game/Game.hpp"
#include "gamelib/Env.hpp"
#include "gamelib/utils/Time.hpp"
#include <ctime>
#include <iostream>

namespace GameLib::Core::Game {

	Game::Game()
	: SPT_(1.0 / GameLib::Env::GAME_TPS), initialized_(false), running_(false), totalTicks_(0) {}

	// State Machine for Step-Based
	void Game::setState(GameState::U_Ptr newState) {
		std::lock_guard<std::mutex> lock(stateMutex_);

		if (currentState_) currentState_->onExit(*this);
		currentState_ = std::move(newState);
		if (currentState_) currentState_->onEnter(*this);
	}

	// 可能要做 update(action)
	void Game::updateState() {
		std::lock_guard<std::mutex> lock(stateMutex_);
		
		if (currentState_) currentState_->onUpdate(*this);
	}

	bool Game::tryStart() {
		try {
			if (running_) throw(std::runtime_error("遊戲正在運行!"));
			if (!initialized_) throw(std::runtime_error("遊戲需要先初始化!"));

			running_ = true;

			// initial setup
			// std::cin.tie(0);
			// std::ios::sync_with_stdio(0);
			// configure_terminal();

			gameThread_ = std::thread([this]() { this->loop(); });

			return true;

		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return false;
		}
	}

	void Game::end() {
		running_ = false;
		if (gameThread_.joinable()) gameThread_.join();
	}

	void Game::loop() {
		auto tickDuration = std::chrono::duration<double>(SPT_);

		while(running_) {
			auto startTime = GameLib::Utils::StedayClock::now();

			updateState();
			++totalTicks_;

			auto endTime = GameLib::Utils::StedayClock::now();
			std::chrono::duration<double> elapsed = endTime - startTime;

			if (elapsed < tickDuration) {
				auto sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(tickDuration - elapsed);
				std::this_thread::sleep_for(sleepTime);
			}
		}
		end();
	}
	
}

