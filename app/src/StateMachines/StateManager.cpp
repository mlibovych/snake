#include "StateManager.h"

StateManager::StateManager(Snake *snake) {
    m_States[Menu] = std::make_unique<MenuState>(snake);
    m_States[Game] = std::make_unique<GameState>(snake);
}

States StateManager::HandleInput(FRKey k) {
    m_States[m_state]->HandleInput(k);
}

bool StateManager::Tick() {
    m_States[m_state]->Tick();
}
