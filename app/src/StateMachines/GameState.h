#pragma once

#include "StateMachines/StateMachineBase.h"

class Snake;

class GameState: public StateMachine {
public:
    GameState(Snake *snake) {
        s = snake;
    }
    ~GameState() {}
    virtual States HandleInput(FRKey k) override {}
    virtual bool Tick() override;

private:
    // member varialbles
};
