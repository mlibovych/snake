#pragma once

#include <map>
#include <array>

#include "Framework.h"

class Snake;

enum States {
    Menu,
    Scoreboard,
    Game,
    Death,
    Count
};

struct Rect {
    int x, y, w, h;
};

struct Button {
    int texture_w, texture_h;
    Sprite *m_texture;
    Rect button_rect;
};

class StateMachine {
public:
    StateMachine(Snake *s) : m_s(s) {}
    virtual ~StateMachine() {};

    virtual void Init() = 0;
    virtual void Enter() = 0;
    virtual States HandleInput(FRKey k) = 0;
    virtual States HandleInput(int32_t k) {}
    virtual States Tick() = 0;
protected:
    // int move_count = 0;
    Snake *m_s;
};
