# 加入 MVC 架構
- 本區功能命名空間
```cpp
using namespace GameLib::Core::Game;
```
---
## `🧬 Model`
- `GameObjectModel` - 遊戲物件的基底類別
- `GamePlayerModel` - 繼承 `GameObjectModel`，遊戲玩家的基底類別

- `UserModel` - 用戶基底類別，允許擴充非遊戲資料，組合 `SessionModel::?_Ptr`

---
## `🖥️ View`
- `IView` - 純虛 View 介面，顯示需要實作自這個介面

- `View` - 實作自 `IView` 的基底類，提供部分基礎實作，純程式 View 可以繼承自此類
- `Screen` - 用來顯示畫面，每個 `View` 同時只能顯示一個 `Screen`
- `BaseUI` - 用來自訂畫面顯示和排版， 每個 `Screen` 和 `BaseUI` 可以具有多個 `BaseUI`

---
## `🕹️ Controller`
> 用來操作遊戲資料，將對應 Model class 注入作為參數

---
### `⬅️ 上一步：` [製作遊戲主架構](docs/getting_started/step1.md)
### `➡️ 下一步：` [加入事件系統](docs/getting_started/step3.md)
1. [製作遊戲主架構](docs/getting_started/step1.md)
2. [加入 MVC 架構](docs/getting_started/step2.md)
3. [加入事件系統](docs/getting_started/step3.md)
4. [使用基礎終端機顯示](docs/getting_started/step4.md)