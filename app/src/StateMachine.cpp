#include "StateMachine.h"

bool StateMachine::Tick(Snake *snake) {
    return std::invoke(m_tick_functions[m_state], this, snake);
}

bool StateMachine::MainMenuTick(Snake *s) {

}

bool StateMachine::PauseTick(Snake *s) {

}

bool StateMachine::DeathTick(Snake *s) {

}

bool StateMachine::ScoreboardTick(Snake *s) {

}

bool StateMachine::GameTick(Snake *s) {
    drawBGColor({0,0,0});
    drawRect(s->m_width, s->m_height, 
             s->m_padding,
             s->m_padding + s->m_menu_height,
             {54,35,194});

    return false;
}
