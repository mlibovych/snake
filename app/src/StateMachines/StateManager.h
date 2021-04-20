#pragma once

#include <memory>

#include "MenuState.h"
#include "GameState.h"
#include "ScoreboardState.h"
#include "DeathState.h"

class Snake;

class StateManager {
public:
    StateManager(Snake *snake);

    void Init();
    void Enter(States state);
    void HandleInput(FRKey k);
    void HandleInput(int32_t k);
    bool Tick();

private:
    std::array<std::unique_ptr<StateMachine>, States::Count> m_States;
    States m_state = Menu;
};
