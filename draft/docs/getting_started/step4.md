# 使用基礎終端機顯示
GameLib 內建一套簡單的 Console 輸出系統，支援：
- 🎨 ASCII 美術渲染（支援彩色、動態）
- 📦 多層級訊息：`info`, `debug`, `warning`, `error`
- 🕹️ 與狀態機 / 模型資料結合，實現動態更新畫面

你可以在 `view/console/` 中找到相關實作，並搭配 Icon 資訊在遊戲畫面中即時顯示模型狀態。


## `🖥️ CONSOLELOG MODULE`

- `ConsoleWindow` - 繼承自 `View`，允許放入 `ConsoleScreen`

- `ConsoleScreen` - 繼承自 `Screen`，允許放入 `ConsoleUI` 之子類和 `ConsoleIcon`

- `ConsoleUI` - 終端機 UI 基底類別
```cpp
pivot_
```

---
#### `⬅️ 上一步：` [加入事件系統](step3.md)
#### `➡️ 下一步：` [使用 TCP/UDP 網路連線](step5.md)