## `GameLib::Core`

- `GameConfig` - 遊戲初始資料，自行繼承並實作並在 `void Game::setup(const GameConfig::S_Ptr)` 使用
```cpp
struct GameConfig {
	using S_Ptr = std::shared_ptr<GameConfig>;
};
```