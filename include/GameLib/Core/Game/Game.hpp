#pragma once

#include "GameConfig.hpp"
#include "GameState.hpp"
#include <unordered_map>
#include <memory>
#include <atomic>
#include <thread>
#include <mutex>

namespace GameLib::Core::Game {
	
	/*
	1. 初始化時需要讀取 `GameLib::Env` 設定 `GAME_TPS`
	2. 子類自行設計存放 Controller 和 Model
	3. 子類需要實做
	`void setup(const GameConfig&)` - `GameConfig` 設定，需要設定 `bool initialized_` 為 `true`，否則無法開始遊戲
	`void start()` - 嘗試開始遊戲
	`void end()` - 遊戲無條件結束，有條件結束需要額外實作，最終呼叫回 end()
	`void reset()` - 清空 `GameConfig` 設定並恢復成建構狀態，若不需要重複使用則保留空實作
	5. `void loop()` 實作基礎流程，遊戲流程透過狀態機實現
	*/
	class Game {
	protected:
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		// 設置
		const double SPT_;
		bool initialized_;
		std::atomic<bool> running_;
		std::thread gameThread_;
		std::mutex stateMutex_;
		
		// 遊戲數值
		GameState::U_Ptr currentState_;
		uint64_t totalTicks_;
		
		// --------------------------------------------------------------------------------
		/*
		TODO: 步進機制與即時機制
		步進如果搭配動畫需要做[允許操作]檢查
		及時機制需要作時間校正、分批處理機制or多執行序
		*/
		void loop();

	public:
		Game();
		virtual ~Game() = default;

		// --------------------------------------------------------------------------------
		// State Machine for Step-Based
		void setState(GameState::U_Ptr);

		// 可能要做 update(action)
		void updateState();

		// --------------------------------------------------------------------------------
		// 初始化遊戲 (GameConfig 可用於繼承 + 指標轉型)
		virtual void setup(const GameConfig::S_Ptr) = 0;

		// 檢查並啟動遊戲
		// 可以自行實作 start() 相關的開始方法
		bool tryStart();

		// 結束遊戲
		// 可以自行實作 win(), lose(), eliminate() 相關的結束方法
		void end();

		// 解除初始化
		virtual void reset() = 0;

		
	};

}

