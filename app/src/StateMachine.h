#pragma once

#include <memory>

enum class States {
    MainMenu,
    Pause,
    Death,
    Scoreboard,
    Game
};

class StateMachine {
public:

private:
    States state;
};
