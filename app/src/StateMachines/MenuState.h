#pragma once

#include "StateMachines/StateMachineBase.h"

#include <string>
#include <map>

class Snake;

const constexpr int g_menu_label_size = 52;
const constexpr Color label_color = {50, 132, 0};
const constexpr int g_text_padding = 10;

enum e_Buttons {
    StartButton,
    ScoreButton,
    ExitButton,
    CountButton
};

class MenuState: public StateMachine {
public:
    MenuState(Snake *snake) : StateMachine(snake) {}
    ~MenuState();

    virtual void Init() override;
    virtual void Enter() override {};
    virtual States HandleInput(FRKey k) override;
    virtual States Tick() override;

private:
    void GenerateButtons();
    Button GenerateButton(const char *text);
    void AlignButtons();

private:
    std::array<Button, CountButton> m_Buttons;
    int m_selected_button = StartButton;
};
