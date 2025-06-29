#pragma once

class IGame {
public:
	IGame(const IGameConfig&);

	void start();
	void end();

	// Implated by derived.
	// void win();
	// void lose();

	void loop();
	void handleOnce();
};