## `GameLib::Core`

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