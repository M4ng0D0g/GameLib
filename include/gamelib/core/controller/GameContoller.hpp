/*

#pragma once

#include "model/Model.h"
#include "Unit.h"
#include "GameConfig.h"
#include <termios.h>
#include <vector>

class Controller {
private:
    Model& model_;
    Direction moveIntent_;

public:
    Controller(const GameConfig& config, Model& model);
    ~Controller();

    bool handleInput();
    void operate();
};

static struct termios old_termios, new_termios;
void reset_terminal();
void configure_terminal();
int read_input();


*/