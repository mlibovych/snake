#include "MenuState.h"

MenuState::~MenuState() {
    for (auto& b : m_Buttons) {
        if (b.m_texture)
            delete b.m_texture;
    }
}

States MenuState::HandleInput(FRKey k) {

}

bool MenuState::Tick() {
    drawBGColor({0,0,0});
    for (auto& b : m_Buttons) {
        drawSprite(b.m_texture, b.button_rect.x, b.button_rect.y);
    }
}

void MenuState::GenerateButtons() {
    std::map<int, std::string> labels = {
        {StartButton, "New Game"},
        {ScoreButton, "Leaderboard"},
        {ExitButton, "Exit"}
    };

    for (int i = 0; i < CountButton; ++i) {
        m_Buttons[i] = GenerateButton(labels[i].c_str(), i);
    }

}

Button MenuState::GenerateButton(const char *text, int i) {
    Button b;

    b.m_texture = generateTextTexture(text, g_menu_label_size, g_label_color, &b.texture_w, &b.texture_h);
    b.button_rect = {g_side_padding, g_top_padding + (b.texture_h * i),
                     b.texture_w + g_text_padding, b.texture_h + g_text_padding};

    return b;
}
