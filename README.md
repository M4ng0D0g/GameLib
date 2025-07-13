# 🎮 GameLib

Useful for simple terminal game.

C++ 遊戲框架，支援 MVC 架構、狀態機、Console View、多執行緒與 Server/Client 模組。  
提供一套輕量、可擴充的基礎架構，讓 C++ 遊戲開發變得更簡單、更有組織，適合用於：

- 回合制或即時制遊戲原型開發
- 學習設計模式（如 MVC、State Machine）
- 終端機互動遊戲系統
- 整合你自己的圖形 / 音效 / 網路等外部 Lib

🚀 **支援擴充性強、模組分離清晰，易於維護與多人協作！**

---

## 📚 文件導覽

- 🧱 [Documentation](docs/documentation.md) - 架構設計與核心模組說明
- 📜 [Changelog](CHANGELOG.md) - 每次更新紀錄與版本變更
- 🧪 `tests/` - 單元測試與使用範例（待補充）

---

## 🖥️ CONSOLELOG 模組

GameLib 內建一套簡單的 Console 輸出系統，支援：
- 🎨 ASCII 美術渲染（支援彩色、動態）
- 📦 多層級訊息：`info`, `debug`, `warning`, `error`
- 🕹️ 與狀態機 / 模型資料結合，實現動態更新畫面

你可以在 `view/console/` 中找到相關實作，並搭配 Icon 資訊在遊戲畫面中即時顯示模型狀態。

---

## 👤 作者資訊

| 作者      | 連結                                  |
|-----------|---------------------------------------|
| M4ng0D0g  | [GitHub 頁面](https://github.com/M4ng0D0g) |

歡迎 PR、Issue 或提出任何建議！

---

## 🛡️ 版權聲明

本專案採用 MIT 授權條款。  
你可以自由使用、修改、散佈，但請保留原始作者與授權資訊。

© 2025 M4ng0D0g. All rights reserved.
