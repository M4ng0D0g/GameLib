# 🎮 GameLib

C++ 遊戲框架，支援 MVC 架構、狀態機、Console View、多執行緒與 Server/Client 模組。  
提供一套輕量、可擴充的基礎架構，讓 C++ 遊戲開發變得更簡單、更有組織，適合用於：

- 回合制或即時制遊戲原型開發
- 學習設計模式（如 MVC、State Machine）
- 終端機互動遊戲系統
- 整合你自己的圖形 / 音效 / 網路等外部 Lib

```
特色：
- 使用 `Game` 為基底管理遊戲流程
- 遊戲邏輯與顯示分離（MVC 架構）
- 支援 Console 顯示（位於 `view/console/`）
- 狀態機管理各階段狀態（位於 `GameState`）
```

🚀 **支援擴充性強、模組分離清晰，易於維護與多人協作！**


# 🛠️ Getting Started
```
想要使用 GameLib 開發，可以依照以下步驟：
```

### 1. 製作遊戲主架構 `GameLib::Core`
#### `🏗️ 遊戲基礎`
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

#### `🔁 狀態機`
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

#### `🎭 MVC架構`

#### Model

- `GameObjectModel` - 遊戲物件的基底類別

---

#### View

- `IView` - 純虛 View 介面，顯示需要實作自這個介面

- `View` - 實作自 `IView` 的基底類，提供部分基礎實作，純程式 View 可以繼承自此類
- `Screen` - 用來顯示畫面，每個 `View` 同時只能顯示一個 `Screen`
- `BaseUI` - 用來自訂畫面顯示和排版， 每個 `Screen` 和 `BaseUI` 可以具有多個 `BaseUI`


---

#### Controller
> 用來操作遊戲資料，將對應 Model class 注入作為參數





## 2. 使用 GameLib 功能優化你的遊戲 (如事件系統、連線、顯示等)，或加入其他 lib

### 事件發布 & 訂閱
- `Event` - 所有事件類型的基底
- `Listener<EventT>` - 監聽特定事件 `EventT` 的監聽器基底
- `EventBus` - 事件總線，用來集合相關的訂閱者和事件

### `GameLib::Network`


```cpp

```
```cpp

```

```md
提供基礎終端機顯示，位於 `view/console`
```
- `ConsoleWindow` - 繼承自 `View`，允許放入 `ConsoleScreen`

- `ConsoleScreen` - 繼承自 `Screen`，允許放入 `ConsoleUI` 之子類和 `ConsoleIcon`

- `ConsoleUI` - 終端機 UI 基底類別
```cpp
pivot_
```



## 3. 設定 `GameLib::Env`
```cpp
// network/Server
static int SERVER_PORT;
static int MAX_CLIENTS;

// core/Game
static double GAME_TPS = 20; // tick(s) per second

```

4. 大功告成



# 🧱 Documentation
- [Documentation](docs/documentation.md) - 架構設計與核心模組說明
- GameCore
	- Game
	- Model
	- View
	- Controller
	- Event
- Network
	- TCP 連線
	- UDP 連線
- Utils 
	- Random Number Generator
	- Time
	- Uuid
- Environment

# 📜 Changelog - 每次更新紀錄與版本變更
# 🧪 `tests/` - 單元測試與使用範例（待補充）

# 🖥️ CONSOLELOG MODULE

GameLib 內建一套簡單的 Console 輸出系統，支援：
- 🎨 ASCII 美術渲染（支援彩色、動態）
- 📦 多層級訊息：`info`, `debug`, `warning`, `error`
- 🕹️ 與狀態機 / 模型資料結合，實現動態更新畫面

你可以在 `view/console/` 中找到相關實作，並搭配 Icon 資訊在遊戲畫面中即時顯示模型狀態。

## 👤 作者資訊

| 作者      | 連結                                  |
|-----------|---------------------------------------|
| M4ng0D0g  | [GitHub 頁面](https://github.com/M4ng0D0g) |

歡迎 PR、Issue 或提出任何建議！

## 🛡️ 版權聲明

本專案採用 MIT 授權條款。  
你可以自由使用、修改、散佈，但請保留原始作者與授權資訊。

© 2025 M4ng0D0g. All rights reserved.
