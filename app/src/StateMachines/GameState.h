#pragma once

#include <chrono>
#include <iostream>

#include "StateMachines/StateMachineBase.h"

class Snake;
enum class Direction;

class GameState: public StateMachine {
public:
    GameState(Snake *snake) : StateMachine(snake) {
        hunger_time = tick_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
    ~GameState() {}

    virtual void Init() {}

    virtual States HandleInput(FRKey k) override;
    
    virtual bool Tick() override;

private:
    uint64_t tick_time, hunger_time;
    Direction head_direction;
    // member varialbles
};
