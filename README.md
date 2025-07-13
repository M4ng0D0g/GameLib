# GameLib
Useful for simple terminal game.

# 基礎設置

### 針對 Class 封裝特定智能指標
```cpp
using Class::U_Ptr = std::unique_ptr<Class>;
using Class::S_Ptr = std::shared_ptr<Class>;
using Class::W_Ptr = std::weak_ptr<Class>;
```

# 主要設計

## GameLib::Core

### 遊戲基礎
- `Game` - 遊戲類必須實作的基底類別，可以存放 Controller 和 Model
- `GameSettings`
> GameEnv
> GameConfig

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
