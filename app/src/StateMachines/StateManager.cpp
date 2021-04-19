#include "StateManager.h"

StateManager::StateManager(Snake *snake) {
    m_States[Menu] = std::make_unique<MenuState>(snake);
    m_States[Game] = std::make_unique<GameState>(snake);
}

void StateManager::Init() {
    // for (auto& s : m_States)
    //     s->Init();

    m_States[Menu]->Init();
    m_States[Game]->Init();
}

void StateManager::HandleInput(FRKey k) {
    if (k == FRKey::ESC) {
        m_state = Menu;
        return;
    }

    States new_state = m_States[m_state]->HandleInput(k);

    if (new_state != m_state) {
        m_state = new_state;
    }
}

bool StateManager::Tick() {
    return m_States[m_state]->Tick();
}
