#include "StateManager.h"

StateManager::StateManager(Snake *snake) {
    m_States[Menu] = std::make_unique<MenuState>(snake);
    m_States[Scoreboard] = std::make_unique<ScoreboardState>(snake);
    m_States[Game] = std::make_unique<GameState>(snake);
}

void StateManager::Init() {
    // for (auto& s : m_States)
    //     s->Init();

    m_States[Menu]->Init();
    m_States[Scoreboard]->Init();
    m_States[Game]->Init();
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

bool StateManager::Tick() {
    drawBGColor({0,0,0});
    States new_state = m_States[m_state]->Tick();

    if (new_state != m_state) {
        Enter(new_state);
    }

    if (m_state == Exit)
        return true;
    else
        return false;
}
