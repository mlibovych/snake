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
    virtual ~StateMachine() {};

    virtual States HandleInput(FRKey k) = 0;
    virtual bool Tick() = 0;
protected:
    Snake* s;
};
