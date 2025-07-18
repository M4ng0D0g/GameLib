## `GameLib::Core`

- `Game` - 遊戲 Class 必須繼承自的基底類別
```cpp
class Game {
public:
	// 初始化遊戲 (GameConfig 可用於繼承 + 指標轉型)
	virtual void setup(const GameConfig::S_Ptr) = 0;

	// 僅負責遊戲邏輯部分，實作需用 `bool tryStart()` 安全啟動遊戲
	virtual void start() = 0;

	// 遊戲結束,有情況結束 (Win/Lose is implated by derived.)
	void end();

	// 解除初始化
	virtual void reset() = 0;
};
```