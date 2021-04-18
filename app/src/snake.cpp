#include "snake.h"

Snake::Snake(int width, int height) noexcept
    : m_width(width), m_height(height)
{
    m_StateMachine = std::make_unique<StateMachine>();
}

void Snake::PreInit(int& width, int& height, bool& fullscreen) noexcept {

}

bool Snake::Init() noexcept {
    
    return true;
}

void Snake::Close() noexcept {

}

bool Snake::Tick() {
    drawBGColor({0,0,0});
    drawRect(100,10,20,20,{54,35,194});
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