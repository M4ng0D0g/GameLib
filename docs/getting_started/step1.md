# 製作遊戲主架構
- 本區功能命名空間
```cpp
using namespace GameLib::Core::Game;
```
- 環境變數命名空間
```cpp
using namespace GameLib::Env;
```

## `🏗️ 遊戲基礎`
- `Game` - 遊戲 Class 必須繼承自的基底類別
```cpp
class Game {
public:
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

protected:
	// 已有安全設計，由 tryStart() 呼叫
	// 實作遊戲邏輯需要透過狀態機
	void loop();
};
```
#### `⚙️ 環境變數`
```cpp
static double GAME_TPS = 20; // tick(s) per second

```

- `GameConfig` - 遊戲初始資料，自行繼承並實作並在 `void Game::setup(const GameConfig::S_Ptr)` 使用
```cpp
struct GameConfig {
	using S_Ptr = std::shared_ptr<GameConfig>;
};
```

---
## `🔁 狀態機`
- `GameState` - 遊戲狀態，放在成員 `Game.currentState_`
```cpp
class GameState {
public:
	using U_Ptr = std::unique_ptr<GameState>;

	virtual void onEnter(Game& game) = 0;
	virtual void onUpdate(Game& game) = 0;
	virtual void onExit(Game& game) = 0;
};
```
```cpp
class Game {
protected:
	GameState::U_Ptr currentState_;
};
```

---
#### `➡️ 下一步：` [加入 MVC 架構](step2.md)