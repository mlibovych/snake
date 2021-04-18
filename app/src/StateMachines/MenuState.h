#pragma once

#include <array>

#include "StateMachines/StateMachineBase.h"

class Snake;
// class StateMachine;

struct Button {
    Sprite *m_texture;
    Rect *button_rect;
};

class MenuState: public StateMachine {
public:
    MenuState() {}
    ~MenuState() {}
    virtual States HandleInput(FRKey k) override {}
    virtual bool Tick() override {}

private:
    std::array<Button, 3> m_Buttons;
    int m_selected_button;
};
