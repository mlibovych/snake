#pragma once

#include <memory>

#include "MenuState.h"
#include "GameState.h"

class Snake;

class StateManager {
public:
    StateManager(Snake *snake);

    void Init() {
        m_States[Menu]->Init();
    }
    States HandleInput(FRKey k);
    bool Tick();

private:
    std::array<std::unique_ptr<StateMachine>, States::Count> m_States;
    States m_state = Game;
    int m_width, m_height;
};
