#pragma once

#include "StateMachines/StateMachineBase.h"

class GameState: public StateMachine {
public:
    GameState() {}
    ~GameState() {}

    virtual void Init() {}
    virtual States HandleInput(FRKey k) override {}
    virtual bool Tick() override {
        drawBGColor({0,0,0});
        // drawRect(s->m_width, s->m_height, 
        //          s->m_padding,
        //          s->m_padding + s->m_menu_height,
        //          {54,35,194});
        drawRect(500, 500, 
             10,
             10,
             {54,35,194});
        
        int w, h;
        drawSprite(generateTextTexture("Test", 24, {200, 10, 100}, &w, &h), 20, 30);

        return false;
    }

private:
    // member varialbles
};
