#pragma once

#include "StateMachines/StateMachineBase.h"

class Snake;

class GameState: public StateMachine {
public:
    GameState(Snake *snake) : StateMachine(snake) {}
    ~GameState() {}

    virtual void Init() override {}
    virtual void Enter() override {}
    virtual States HandleInput(FRKey k) override {if (k == FRKey::ESC) return Menu; else return Game;}
    virtual bool Tick() override;

private:
    // member varialbles
};
