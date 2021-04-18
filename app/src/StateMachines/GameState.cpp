#include "GameState.h"

#include "../snake.h"

bool GameState::Tick() {
    drawBGColor({0,0,0});
    drawRect(s->m_width, s->m_height, 
                s->m_padding,
                s->m_padding + s->m_menu_height,
                {54,35,194});
    
    drawSprite(generateTextTexture("Test", 24, {200, 10, 100}), 20, 30);

    return false;
}