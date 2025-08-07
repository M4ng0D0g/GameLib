#pragma once

#include "Game.hpp"
#include "interface/IGameManager.hpp"
#include <type_traits>
#include <vector>
#include <memory>

namespace gamelib::game {

	using Token = uint32_t;

	template <typename GameT>
	class GameManager : public interface::IGameManager {
		static_assert(std::is_base_of<Game, GameT>::value, "GameT 必須繼承 Game");
	public:
		GameManager(size_t maxGameCnt) : MaxGameCnt_(maxGameCnt), games_(maxGameCnt) {}

		void createGame() override {
			
		}

		bool handleEvent() override {

		}

		
		

	private:
		const size_t MaxGameCnt_;
		std::vector<std::unique_ptr<GameT>> games_;

	};
}