#pragma once

#include "MenuState.h"
#include "GameState.h"

class Snake;

class StateManager {
public:
    StateManager(Snake *snake);

    States HandleInput(FRKey k);
    bool Tick();

private:
    std::array<std::unique_ptr<StateMachine>, States::Count> m_States;
    States m_state = Game;
    int m_width, m_height;
};
