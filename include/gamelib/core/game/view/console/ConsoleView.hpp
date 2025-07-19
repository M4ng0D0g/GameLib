#pragma once

#include "gamelib/core/view/IView.hpp"
#include "gamelib/utils/Unit.hpp"
#include "gamelib/utils/AnsiPrint.hpp"
#include "ui/ConsoleUI.hpp"
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <memory>

namespace GameLib::Core {

	class ConsoleView : public IView {
	public:
		using U_Ptr = std::unique_ptr<ConsoleView>;

	private:
		// IModel::Ptr& model_; // 改用吃參數

		std::vector<BaseUI::Ptr> ui_;



		int _termWidth;
		int _termHeight;
		std::vector<std::vector<std::string>> latest_map, last_map;
		std::vector<std::vector<AnsiColor::Ptr>> latest_fg_color, last_fg_color;
		std::vector<std::vector<AnsiColor::Ptr>> latest_bg_color, last_bg_color;
		static std::pair<int, int> get_terminal_size();

	public:
		ConsoleView(const IGameConfig::Ptr& config, IModel::Ptr& model);

		void update() override;
		void render() const override;
		void resetLatest();

	};
}



