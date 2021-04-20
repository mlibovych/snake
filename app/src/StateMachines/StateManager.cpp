#include "StateManager.h"

StateManager::StateManager(Snake *snake) {
    m_States[Menu] = std::make_unique<MenuState>(snake);
    m_States[Scoreboard] = std::make_unique<ScoreboardState>(snake);
    m_States[Game] = std::make_unique<GameState>(snake);
    m_States[Death] = std::make_unique<DeathState>(snake);
}

void StateManager::Init() {
    for (auto& s : m_States)
        s->Init();
}

void StateManager::Enter(States state) {
    m_state = state;

    m_States[state]->Enter();
}

void StateManager::HandleInput(FRKey k) {
    States new_state = m_States[m_state]->HandleInput(k);

    if (new_state != m_state) {
        Enter(new_state);
    }
}

void StateManager::HandleInput(int32_t k) {
    if (m_state != Death)
        return;

    States new_state = m_States[m_state]->HandleInput(k);
}

bool StateManager::Tick() {
    drawBGColor({0,0,0});
    States new_state = m_States[m_state]->Tick();

    if (new_state != m_state) {
        Enter(new_state);
    }

    return false;
}
