#include "StateManager.h"

StateManager::StateManager() {
    m_States[Menu] = std::make_unique<MenuState>();
    m_States[Game] = std::make_unique<GameState>();
}

States StateManager::HandleInput(FRKey k) {
    m_States[m_state]->HandleInput(k);
}

bool StateManager::Tick() {
    m_States[m_state]->Tick();
}
