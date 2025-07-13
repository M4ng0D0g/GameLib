# GameLib
Useful for simple terminal game.

---

# Documentation

## `GameLib::Env`
```cpp
// connect/Server
static int SERVER_PORT;
static int MAX_CLIENTS;

// core/Game
static double GAME_TPS; // tick(s) per second

```


## `GameLib::Core`

### 遊戲基礎

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

- `GameConfig` - 遊戲初始資料，自行繼承並實作並在 `void Game::setup(const GameConfig::S_Ptr)` 使用
```cpp
struct GameConfig {
	using S_Ptr = std::shared_ptr<GameConfig>;
};
```

### 狀態機

- `GameState` - 遊戲狀態，放在變數 `Game.currentState_`
```cpp
class GameState {
public:
	using U_Ptr = std::unique_ptr<GameState>;

	virtual void onEnter(Game& game) = 0;
	virtual void onUpdate(Game& game) = 0;
	virtual void onExit(Game& game) = 0;
};
```

### 事件發布 & 訂閱

### Model
用來存放遊戲資料，由 Game class 管控，需要提供特定獲取資料方式

### Controller
用來操作遊戲資料，將對應 Model class 注入作為參數

### View
用來顯示，需要提供特定方法

# [UI]

- 提供基礎終端機模板

# [Connection]


```cpp

```
```cpp

```