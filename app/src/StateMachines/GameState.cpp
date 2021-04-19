#include "GameState.h"

#include "../snake.h"

using namespace std::chrono;

bool GameState::Tick() {
    uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    //draw field
    drawBGColor({0,0,0});
    drawRect(m_s->m_playfield_w, m_s->m_playfield_height, 
                m_s->m_padding,
                m_s->m_padding + m_s->m_menu_height,
                {54,35,194});

    //growing
    if (now - hunger_time >= 4000) {
        hunger_time = now;
        m_s->snake.pop_back();
    }
    //move
    if (now - tick_time > 100) {
        tick_time = now;
        m_s->snake.front().direction = head_direction;
        m_s->Move();
    }
    //draw snake
    for (const auto& piece : m_s->snake) {
        drawSprite(piece.sprite, piece.x, piece.y);
    }
    //check state
    return false;
}

States GameState::HandleInput(FRKey k) {
    if (k == FRKey::ESC) return Menu;

    Direction& direction = m_s->snake.front().direction;
    if (direction == Direction::UP ||
        direction == Direction::DOWN) {
        switch (k) {
        case FRKey::LEFT:
            head_direction = Direction::LEFT;
            break;
        case FRKey::RIGHT:
            head_direction = Direction::RIGHT;
            break;
        default:
            break;
        }
    }
    else if (direction == Direction::RIGHT ||
            direction == Direction::LEFT) {
        switch (k) {
        case FRKey::DOWN:
            head_direction = Direction::DOWN;
            break;
        case FRKey::UP:
            head_direction = Direction::UP;
            break;
        default:
            break;
        }
    }
    return Game;
}
