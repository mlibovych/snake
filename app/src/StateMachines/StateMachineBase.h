#pragma once

#include <map>
#include <array>

#include "Framework.h"

class Snake;

enum States {
    Menu,
    Pause,
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
    virtual void Enter() = 0;
    virtual States HandleInput(FRKey k) = 0;
    virtual bool Tick() = 0;
protected:
    Snake *m_s;
};
