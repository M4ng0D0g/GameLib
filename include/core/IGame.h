#pragma once

class IGame {
public:
	virtual ~IGame() = default;

	// State Machine for Step-Based
	virtual void update() = 0;

	virtual void start() = 0;
	virtual void end() = 0;

	/*
	virtual void end(...) = 0; 有情況結束(Implated by derived.)
	void win();
	void lose();
	*/

	/*
	TODO: 步進機制與即時機制
	步進如果搭配動畫需要做[允許操作]檢查
	及時機制需要作時間校正、分批處理機制or多執行序
	*/
	virtual void loop() = 0;

	/*
	handleOnce() 的工作：
	1. 依照流程處理事件：如果是回合制 -> 丟給狀態機處理，如果是即時制 -> 照流程處理
	2. 可能存在多個工作流程：
	*/
	virtual void handleOnce() = 0;
};