#pragma once

#include "StateMachines/StateMachineBase.h"

#include <string>
#include <map>
#include <filesystem>
#include <chrono>
#include <fstream>
#include <iostream>

class Snake;

struct Score {
    std::string name;
    std::string points;
    Sprite *m_texture = nullptr;
    int tex_w, tex_h;
};

class ScoreboardState: public StateMachine {
public:
    ScoreboardState(Snake *snake) : StateMachine(snake) {}
    virtual ~ScoreboardState() {}

    virtual void Init() override;
    virtual void Enter() override;
    virtual States HandleInput(FRKey k) override;
    virtual States Tick() override;

private:
    void UpdateLeaderboard(std::istream& file);
    void CreateTextTexture(int i);

private:
    std::array<Score, 10> m_Leaders;
    std::filesystem::file_time_type m_last_write_time;
    int side_padding, top_padding;

    const static constexpr int max_name_len = 8;
    const static constexpr int max_score_len = 5;
    const static constexpr int dots_between = 10;
    const static constexpr Color label_color = {50, 132, 0};
    const static constexpr int text_padding = 10;
    int text_size = 30;
};