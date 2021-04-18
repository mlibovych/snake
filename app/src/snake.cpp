#include "snake.h"

Snake::Snake(int width, int height) noexcept
    : m_width(width), m_height(height)
{
    m_StateManager = std::make_unique<StateManager>(this);
}

void Snake::PreInit(int& width, int& height, bool& fullscreen) noexcept {
    width = m_width + (2 * m_padding);
    height = m_height + m_menu_height + (2 * m_padding);
}

bool Snake::Init() noexcept {
    
    snake.push_back({createSprite("app/resources/head.png"),
                    (m_width + (2 * m_padding)) /2 - cell_width / 2,
                    m_height / 2  + m_menu_height + m_padding - cell_width / 2,
                    Direction::UP});
    for (int i = 0; i < 3; ++i) {
        Grow();
    }
    m_StateManager->Init();
    return true;
}

void Snake::Grow() noexcept {
    auto tail = snake.back();
    int x = tail.x;
    int y = tail.y;

    switch (tail.direction) {
    case Direction::UP:
        y += cell_width;
        break;
    case Direction::DOWN:
        y -= cell_width;
        break;
    case Direction::LEFT:
        x += cell_width;
        break;
    case Direction::RIGHT:
        x -= cell_width;
        break;
    default:
        break;
    }

    snake.push_back({createSprite("app/resources/body.png"),
                    x,
                    y,
                    tail.direction});
}

void Snake::Move() noexcept {
    for (auto& piece : snake) {
        switch (piece.direction) {
        case Direction::UP:
            piece.y -= cell_width;
            break;
        case Direction::DOWN:
            piece.y += cell_width;
            break;
        case Direction::LEFT:
            piece.x -= cell_width;
            break;
        case Direction::RIGHT:
            piece.x += cell_width;
            break;
        default:
            break;
        }
    };
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
    m_StateManager->HandleInput(k);
}

void Snake::onKeyReleased(FRKey k) noexcept {

}

bool Snake::onQuitEvent(uint32_t win_id) noexcept {

}

const char* Snake::GetTitle() noexcept {
    return "The Snake: Chaurus Reaper Invasion";
}