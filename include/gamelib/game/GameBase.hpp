#pragma once

#include "GameConfigBase.hpp"
#include "StateBase.hpp"
#include <unordered_map>
#include <memory>
#include <atomic>
#include <thread>
#include <mutex>

namespace gamelib::game {
	
	/*
	1. 需要用 void setup(const GameConfig&) 設定 `GAME_TPS`
	2. 子類自行設計存放 Controller 和 Model
	3. 子類需要實做
	`void setup(const GameConfig&)` - `GameConfig` 設定，需要設定 `bool initialized_` 為 `true`，否則無法開始遊戲
	`void start()` - 嘗試開始遊戲
	`void end()` - 遊戲無條件結束，有條件結束需要額外實作，最終呼叫回 end()
	`void reset()` - 清空 `GameConfig` 設定並恢復成建構狀態，若不需要重複使用則保留空實作
	5. `void loop()` 實作基礎流程，遊戲流程透過狀態機實現
	*/

	class GameBase {
	public:
		GameBase();
		virtual ~GameBase() = default;

	protected:
		GameBase(const GameBase&) = delete;
		GameBase& operator=(const GameBase&) = delete;

		// --------------------------------------------------------------------------------
		// getter
		const double& SPT() const {
			return SPT_;
		}

		const uint64_t& totalTicks() const {
			return totalTicks_;
		}
		
		// --------------------------------------------------------------------------------
		// State Machine for Step-Based
		void setState(std::unique_ptr<StateBase>);

		// --------------------------------------------------------------------------------
		// 初始化遊戲 (GameConfig 可用於繼承 + 指標轉型)
		void setupBase(const GameConfigBase& config);

		// 檢查並啟動遊戲
		// 可以自行實作 start() 相關的開始方法
		bool safetyStart();

		// 結束遊戲
		// 可以自行實作 win(), lose(), eliminate() 相關的結束方法
		void terminate();

		// 解除初始化
		// virtual void reset() = 0;

	private:
		// 設置
		double SPT_ = -1;
		bool initialized_;
		std::atomic<bool> running_;
		std::thread gameThread_;
		std::mutex stateMutex_;
		
		// 遊戲數值
		std::unique_ptr<StateBase> coreStateCur_;
		uint64_t totalTicks_;

		// --------------------------------------------------------------------------------
		// 可能要做 update(action)
		void updateState();

		// --------------------------------------------------------------------------------
		/*
		TODO: 步進機制與即時機制
		步進如果搭配動畫需要做[允許操作]檢查
		及時機制需要作時間校正、分批處理機制or多執行序
		*/
		void loop();

	};

}

