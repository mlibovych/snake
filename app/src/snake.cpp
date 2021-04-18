#include "snake.h"

Snake::Snake(int width, int height) noexcept
    : m_width(width), m_height(height)
{
    m_StateManager = std::make_unique<StateManager>();
}

void Snake::PreInit(int& width, int& height, bool& fullscreen) noexcept {
    width = m_width + (2 * m_padding);
    height = m_height + m_menu_height + (2 * m_padding);
}

bool Snake::Init() noexcept {
    m_StateManager->Init();
    return true;
}

void Snake::Close() noexcept {

}

bool Snake::Tick() {
    return m_StateManager->Tick();
}

void Snake::onMouseMove(int x, int y, int xrelative, int yrelative) noexcept {

}

void Snake::onMouseButtonClick(FRMouseButton button, bool isReleased) noexcept {

}

void Snake::onKeyPressed(FRKey k) noexcept {

}

void Snake::onKeyReleased(FRKey k) noexcept {

}

bool Snake::onQuitEvent(uint32_t win_id) noexcept {

}

const char* Snake::GetTitle() noexcept {
    return "The Snake: Chaurus Reaper Invasion";
}