#pragma once

#include "StateMachines/StateMachineBase.h"

#include <string>
#include <map>

class Snake;

const constexpr int g_menu_label_size = 36;
const constexpr Color g_label_color = {50, 132, 0};
const constexpr int g_text_padding = 10;

enum e_Buttons {
    StartButton,
    ScoreButton,
    ExitButton,
    CountButton
};

struct Button {
    int texture_w, texture_h;
    Sprite *m_texture;
    Rect button_rect;
};

class MenuState: public StateMachine {
public:
    MenuState(Snake *snake) : StateMachine(snake) {}
    ~MenuState();

    void Init() override {
        GenerateButtons();
    }
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
