#pragma once

#include <chrono>
#include <iostream>
#include <list>
#include <random>
#include <unordered_map>
#include <deque>

#include "StateMachines/StateMachineBase.h"

class Snake;
struct Color;

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

    void drawScore();

    void Load();

private:
    int speed = 200;
    std::list<Piece> snake;
    uint64_t tick_time, hunger_time;
    Direction head_direction;
    Piece food;
    Sprite *score_label;
    std::unordered_map<int, Sprite*> numbers;
    int score_w, score_h;
};
