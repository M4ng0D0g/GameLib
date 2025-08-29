#include "gamelib/game/GameBase.hpp"
#include "gamelib/game/GameConfigBase.hpp"
#include "gamelib/utils/Time.hpp"
#include <ctime>
#include <iostream>

namespace gamelib::game {

	GameBase::GameBase() : initialized_(false), running_(false), totalTicks_(0) {}

	// State Machine for Step-Based
	void GameBase::setState(std::unique_ptr<StateBase> newState) {
		std::lock_guard<std::mutex> lock(stateMutex_);

		if (coreStateCur_) coreStateCur_->onExit(*this);
		coreStateCur_ = std::move(newState);
		if (coreStateCur_) coreStateCur_->onEnter(*this);
	}

	// 可能要做 update(action)
	void GameBase::updateState() {
		std::lock_guard<std::mutex> lock(stateMutex_);
		
		if (coreStateCur_) coreStateCur_->onUpdate(*this);
	}

	void GameBase::setupBase(const GameConfigBase& config) {
		if (config.GAME_TPS <= 0) throw(std::logic_error("SPT_ 不可 <= 0"));
		SPT_ = 1.0 / config.GAME_TPS;

		initialized_ = true;
	}

	bool GameBase::safetyStart() {
		try {
			if (running_) throw(std::logic_error("遊戲正在運行!"));
			if (!initialized_) throw(std::logic_error("遊戲需要先初始化!"));

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

	void GameBase::terminate() {
		running_ = false;
		if (gameThread_.joinable()) gameThread_.join();
	}

	void GameBase::loop() {
		auto tickDuration = static_cast<unsigned long>(SPT_);
		
		while(running_) {
			if (!coreStateCur_) {
				throw(std::logic_error("coreStateCur_ 為 nullptr, 遊戲中止"));
				running_ = false;
				break;
			}

			auto startTime = gamelib::utils::steadyNowMs();

			updateState();
			++totalTicks_;

			auto endTime = gamelib::utils::steadyNowMs();
			auto elapsed = endTime - startTime;

			if (elapsed < tickDuration) {
				auto sleepTime = tickDuration - elapsed;
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
			}
		}
	}
}

