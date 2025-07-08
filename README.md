# GameLib
Useful for simple terminal game.

# [Game]

## IGame
Game class 必須實作的基底類別，可以存放 IController 和 IModel
- 在 handleOnce() 實作單次遊戲流程，loop() 照設計運行 handleOnce()

## IModel
用來存放遊戲資料，由 Game class 管控，需要提供特定獲取資料方式

## IController
用來操作遊戲資料，將對應 Model class 注入作為參數

## IView
用來顯示，需要提供特定方法

# [UI]

- 提供基礎終端機模板

# [Connection]
