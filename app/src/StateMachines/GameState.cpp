#include "GameState.h"

#include "../snake.h"

bool GameState::Tick() {
    drawBGColor({0,0,0});
    drawRect(m_s->m_width, m_s->m_height, 
                m_s->m_padding,
                m_s->m_padding + m_s->m_menu_height,
                {54,35,194});
    m_s->Move();
    //check colision
    for (const auto& piece : m_s->snake) {
        drawSprite(piece.sprite, piece.x, piece.y);
    }
    return false;
}

States GameState::HandleInput(FRKey k) {
    Direction& direction = m_s->snake.front().direction;
    // if (direction == Direction::UP ||
    //     direction == Direction::DOWN) {
    //     switch (k) {
    //     case FRKey::LEFT:
    //         direction = Direction::LEFT;
    //         break;
    //     case FRKey::RIGHT:
    //         direction = Direction::RIGHT;
    //         break;
    //     default:
    //         break;
    //     }
    // }
    // else if (direction == Direction::RIGHT ||
    //         direction == Direction::LEFT) {
    //     switch (k) {
    //     case FRKey::DOWN:
    //         direction = Direction::DOWN;
    //         break;
    //     case FRKey::UP:
    //         direction = Direction::UP;
    //         break;
    //     default:
    //         break;
    //     }
    // }
    
}