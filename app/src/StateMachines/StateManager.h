#pragma once

#include "MenuState.h"
#include "GameState.h"

class StateManager {
public:
    StateManager();

    void Init() {
        m_States[Menu]->Init();
    }
    States HandleInput(FRKey k);
    bool Tick();

private:
    std::array<std::unique_ptr<StateMachine>, States::Count> m_States;
    States m_state = Menu;
};
