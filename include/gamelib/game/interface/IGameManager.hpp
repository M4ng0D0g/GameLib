#pragma once

namespace gamelib::game::interface {

	class IGameManager {
	public:
		virtual ~IGameManager() = default;

		virtual void createGame() = 0;
		virtual bool handleEvent() = 0;
	};
}