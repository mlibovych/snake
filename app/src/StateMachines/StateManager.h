#pragma once

#include <memory>

#include "MenuState.h"
#include "GameState.h"

class Snake;

class StateManager {
public:
    StateManager(Snake *snake);

    void Init();
    void HandleInput(FRKey k);
    void Tick();

private:
    std::array<std::unique_ptr<StateMachine>, States::Count> m_States;
    States m_state = Game;
    int m_width, m_height;
};
