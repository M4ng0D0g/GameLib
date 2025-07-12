#pragma once

#include <memory>

class IView {
public:
	using Ptr = std::unique_ptr<IView>;

	virtual void update() = 0;
	virtual void render() const = 0;
};

/*
#pragma once

#include "Unit.h"
#include "GameConfig.h"
#include "view/AnsiPrint.h"
#include "model/Model.h"
#include <string>
#include <vector>
#include <string>
#include <utility>

class View {
private:
    const GameConfig& config_;
    Model& model_;

    int _termWidth;
    int _termHeight;
    std::vector<std::vector<std::string>> latest_map, last_map;
    std::vector<std::vector<AnsiColor::Ptr>> latest_fg_color, last_fg_color;
    std::vector<std::vector<AnsiColor::Ptr>> latest_bg_color, last_bg_color;
    static std::pair<int, int> get_terminal_size();

public:
    View(const GameConfig& config, Model& model);

    void updateGameObject();
    void render();
    void displayScore();
    
    void resetLatest();


};


*/