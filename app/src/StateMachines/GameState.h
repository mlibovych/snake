#pragma once

#include "StateMachines/StateMachineBase.h"

class Snake;

class GameState: public StateMachine {
public:
    GameState(Snake *snake) : StateMachine(snake) {}
    ~GameState() {}

    virtual void Init() {}
    virtual States HandleInput(FRKey k) override;
    virtual bool Tick() override;

private:
    // member varialbles
};
