#pragma once

#include <chrono>
#include <iostream>
#include <list>
#include <random>

#include "StateMachines/StateMachineBase.h"

class Snake;

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	COUNT
};

struct Piece {
	Sprite* sprite;
	int x, y;
	Direction direction;
};

class GameState: public StateMachine {
public:
    GameState(Snake *snake) : StateMachine(snake) {
        hunger_time = tick_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
    ~GameState() {}

    virtual void Init();

    virtual States HandleInput(FRKey k) override;
    
    virtual States Tick() override;

    void Grow() noexcept;

	void Move() noexcept;

    bool CheckCollision();

    bool CheckCollision(Piece& lhs, Piece& rhs);

    void SpawnFood();

private:
    int speed = 200;
    std::list<Piece> snake;
    uint64_t tick_time, hunger_time;
    Direction head_direction;
    Piece food;
    // member varialbles
};
