#include "GameState.h"

#include "../snake.h"

bool GameState::Tick() {
    drawBGColor({0,0,0});
    // drawRect(m_s->m_width, m_s->m_height, 
    //          m_s->m_padding,
    //          m_s->m_padding + m_s->m_menu_height,
    //          {54,35,194});
    
    int w, h;
    drawSprite(generateTextTexture("Test", 24, {200, 10, 100}, &w, &h), 20, 30);

    return false;
}