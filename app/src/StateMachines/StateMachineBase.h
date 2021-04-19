#pragma once

#include <map>
#include <array>

#include "Framework.h"

class Snake;

enum States {
    Menu,
    Pause,
    Death,
    Scoreboard,
    Game,
    Count
};

struct Rect {
    int x, y, w, h;
};

class StateMachine {
public:
    StateMachine(Snake *s) : m_s(s) {}
    virtual ~StateMachine() {};

    virtual void Init() = 0;
    virtual States HandleInput(FRKey k) = 0;
    virtual States Tick() = 0;
protected:
    // int move_count = 0;
    Snake *m_s;
};
