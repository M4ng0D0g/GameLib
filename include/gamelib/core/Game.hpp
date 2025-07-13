#pragma once

#include "GameConfig.hpp"
#include "GameState.hpp"
#include <unordered_map>
#include <memory>
#include <atomic>

namespace GameLib::Core {

	class Game {
	protected:
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		GameState::U_Ptr currentState_;
		const double SPT_;

		bool initialized_{false};
		std::atomic<bool> running_{false};

	public:
		Game();
		virtual ~Game() = default;

		// --------------------------------------------------------------------------------
		// State Machine for Step-Based
		void setState(std::unique_ptr<GameState>);

		// 可能要做 update(action)
		void updateState();

		// --------------------------------------------------------------------------------
		// 初始化遊戲
		virtual void setup(const GameConfig& config) = 0;

		// 確認初始化才開始
		virtual void start() = 0;

		// 遊戲結束,有情況結束(Win/Lose is implated by derived.)
		virtual void end() = 0;

		// 解除初始化
		virtual void reset() = 0;


		// --------------------------------------------------------------------------------
		/*
		TODO: 步進機制與即時機制
		步進如果搭配動畫需要做[允許操作]檢查
		及時機制需要作時間校正、分批處理機制or多執行序
		*/
		void loop();

		/*
		handleOnce() 的工作(棄用)：
		1. 依照流程處理事件：如果是回合制 -> 丟給狀態機處理，如果是即時制 -> 照流程處理
		2. 可能存在多個工作流程：
		*/
		//virtual void handleOnce() = 0;
	};

}

