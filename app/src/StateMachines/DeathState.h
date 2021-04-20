#pragma once

#include "StateMachines/StateMachineBase.h"
#include <string>
#include <fstream>

class Snake;

class DeathState: public StateMachine {
public:
    DeathState(Snake *snake) : StateMachine(snake) {}
    ~DeathState() {}

    virtual void Init() override;
    virtual void Enter() override;
    virtual States HandleInput(FRKey k) override;
    virtual States HandleInput(int32_t k) override;
    virtual States Tick() override;

private:
    void SaveScore();

private:
    const static constexpr Color label_color = {50, 132, 0};
    const static constexpr int text_padding = 30;
    const static constexpr int letter_padding = 20;
    const static constexpr int max_name_len = 8;

    Button m_label1;
    Button m_label2;
    std::map<char, Button> m_letters;
    std::string m_username;
    int m_text_size_labels = 40;
    Rect m_input_rect;
};