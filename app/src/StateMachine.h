#pragma once

#include <map>

#include "Framework.h"
#include "snake.h"

class Snake;

enum States {
    MainMenu,
    Pause,
    Death,
    Scoreboard,
    Game
};

class StateMachine {
public:
    bool Tick(Snake *snake);

private:
    bool MainMenuTick(Snake *snake);
    bool PauseTick(Snake *snake);
    bool DeathTick(Snake *snake);
    bool ScoreboardTick(Snake *snake);
    bool GameTick(Snake *snake);

private:
    States m_state = Game;
    std::map<int, bool (StateMachine::*)(Snake*)> m_tick_functions = {
        {MainMenu, &StateMachine::MainMenuTick},
        {Pause, &StateMachine::PauseTick},
        {Death, &StateMachine::DeathTick},
        {Scoreboard, &StateMachine::ScoreboardTick},
        {Game, &StateMachine::GameTick},
    };
};
