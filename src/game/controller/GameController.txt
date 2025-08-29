/*
#include <iostream>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <chrono>
#include <algorithm>
#include "controller/Controller.h"

Controller::Controller(const GameConfig& config, Model& model) : model_(model) {}
Controller::~Controller() {}

bool Controller::handleInput() {
    int keyInput = -1;
    keyInput = read_input();
    // std::cout << "Key: " << keyInput << std::endl;

    // ESC to exit program
    if(keyInput==27) return false;
    // If there is no input, do nothing.
    // if(keyInput==-1) return true;

    // TODO 
    // handle key events.
    switch(keyInput) {
        case 'W': case 'w': moveIntent_ = Direction::UP; break;
        case 'A': case 'a': moveIntent_ = Direction::LEFT; break;
        case 'S': case 's': moveIntent_ = Direction::DOWN; break;
        case 'D': case 'd': moveIntent_ = Direction::RIGHT; break;
        default: moveIntent_ = Direction::STOP; break;
    }
    return true;
}
void Controller::operate() {
    if(moveIntent_ == Direction::STOP) return;

    model_.resetStatus();
    if(model_.moveTiles(moveIntent_)) {
        model_.converseBoard();
        

        auto tile = model_.summonTile();
        model_.placeTile(moveIntent_, tile);

        model_.updateStatus();
    }
    else model_.notUpdateStatus();
}

void reset_terminal() {
    printf("\e[m"); // reset color changes
    printf("\e[?25h"); // show cursor
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// terminal initial configuration setup
void configure_terminal() {
    tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios; // save it to be able to reset on exit
    
    new_termios.c_lflag &= ~(ICANON | ECHO); // turn off echo + non-canonical mode
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    printf("\e[?25l"); // hide cursor
    std::atexit(reset_terminal);
}


int read_input() {
    fflush(stdout);
   	char buf[4096]; // maximum input buffer
	int n = read(STDIN_FILENO, buf, sizeof(buf));
    return n > 0 ? buf[n - 1] : -1;
}


*/