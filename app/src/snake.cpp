#include "snake.h"

Snake::Snake(int width, int height) noexcept
    : m_playfield_w(width), m_playfield_h(height)
{
    m_playfield_w -= m_playfield_w % cell_width;
    m_playfield_h -= m_playfield_h % cell_width;
    m_window_w = m_playfield_w + (2 * m_padding);
    m_window_h = m_playfield_h + m_menu_height + (2 * m_padding);
    m_StateManager = std::make_unique<StateManager>(this);
}

void Snake::PreInit(int& width, int& height, bool& fullscreen) noexcept {
    width = m_window_w;
    height = m_window_h;
    fullscreen = false;
}

bool Snake::Init() noexcept {
    m_StateManager->Init();
    return true;
}

void Snake::Close() noexcept {

}

bool Snake::Tick() {
    if (m_quit)
        return true;

    m_StateManager->Tick();
    return false;
}

void Snake::onKeyPressed(FRKey k) noexcept {
    m_StateManager->HandleInput(k);
}

void Snake::onKeyReleased(FRKey k) noexcept {

}

const char* Snake::GetTitle() noexcept {
    return "The Snake: Chaurus Reaper Invasion";
}