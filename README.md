# GameLib
Useful for simple terminal game.

## 基礎設置

### 針對 Class 封裝特定智能指標
```cpp
using Class::U_Ptr = std::unique_ptr<Class>;
using Class::S_Ptr = std::shared_ptr<Class>;
using Class::W_Ptr = std::weak_ptr<Class>;
```

---

# 主要設計

## `GameLib::Core`

### 遊戲基礎

- **[Class]** `Game` - 遊戲 Class 必須繼承自的基底類別
	1. 初始化時需要讀取 `GameLib::Env` 設定 `GAME_TPS`
	2. 子類自行設計存放 Controller 和 Model
	3. 子類需要實做 `void setup(const GameConfig&)`, `void start()`, `void end()`, `void reset()`
	4. `void setup(const GameConfig&)` 需要設定 `bool initialized_` 為 `true`，否則無法開始遊戲
	5. `Game` 已在 `void loop()` 實作基礎流程，遊戲流程透過狀態機實現

- **[Struct]** `GameConfig` - 遊戲初始資料，自行設計並在 `void Game::setup(const GameConfig&)` 使用

### 狀態機
- `GameState`

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
