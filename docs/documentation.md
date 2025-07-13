# 📖 Documentation

### 🎯 架構概述

- 使用 `Game` 為基底管理遊戲流程
- 遊戲邏輯與顯示分離（MVC 架構）
- 支援 Console 顯示（位於 `view/console/`）
- 狀態機管理各階段狀態（位於 `GameState`）

## 📚 目錄

- 🧱 [架構設計](docs/architecture.md)
- 🧵 [多執行緒設計](docs/threading.md)

## `GameLib::Env`
```cpp
// network/Server
static int SERVER_PORT;
static int MAX_CLIENTS;

// core/Game
static double GAME_TPS; // tick(s) per second

```


## `GameLib::Core`

### 🎮 遊戲基礎

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

### 🔁 狀態機設計

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

## MVC架構

### Model

- `GameObjectModel` - 遊戲物件的基底類別

---

### View

- `IView` - 純虛 View 介面，顯示需要實作自這個介面

- `View` - 實作自 `IView` 的基底類，提供部分基礎實作，純程式 View 可以繼承自此類
- `Screen` - 用來顯示畫面，每個 `View` 同時只能顯示一個 `Screen`
- `BaseUI` - 用來自訂畫面顯示和排版， 每個 `Screen` 和 `BaseUI` 可以具有多個 `BaseUI`

```md
提供基礎終端機顯示，位於 `view/console`
```
- `ConsoleWindow` - 繼承自 `View`，允許放入 `ConsoleScreen`

- `ConsoleScreen` - 繼承自 `Screen`，允許放入 `ConsoleUI` 之子類和 `ConsoleIcon`

- `ConsoleUI` - 終端機 UI 基底類別
```cpp
pivot_
```

---

### Controller
> 用來操作遊戲資料，將對應 Model class 注入作為參數


## `GameLib::Network`


```cpp

```
```cpp

```