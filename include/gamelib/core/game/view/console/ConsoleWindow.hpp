#pragma once
	
class ConsoleWindow {
public:
  static ConsoleWindow& instance() {
        static ConsoleWindow inst;
        return inst;
    }

private:
    ConsoleWindow() = default;
    bool visible = true;
};
