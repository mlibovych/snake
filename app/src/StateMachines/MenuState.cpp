#include "MenuState.h"
#include "../snake.h"

MenuState::~MenuState() {
    for (auto& b : m_Buttons) {
        if (b.m_texture)
            delete b.m_texture;
    }
}

void MenuState::Init() {
    GenerateButtons();
}

States MenuState::HandleInput(FRKey k) {
    if (k == FRKey::ENTER) {
        if (m_selected_button == StartButton)
            return Game;
        else if (m_selected_button == ScoreButton)
            return Scoreboard;
        else if (m_selected_button == ExitButton) {
            m_s->m_quit = true;
            return Menu;
        }
    }
    
    if (k == FRKey::DOWN)
        m_selected_button += 1;
    else if (k == FRKey::UP)
        m_selected_button -= 1;        

    if (m_selected_button < 0)
        m_selected_button = CountButton - 1;
    else if (m_selected_button >= CountButton)
        m_selected_button = 0;

    return Menu;
}

bool MenuState::Tick() {
    drawBGColor({0,0,0});

    Rect &r = m_Buttons[m_selected_button].button_rect;
    drawRect(r.w, r.h, r.x, r.y, {24, 42, 2});

    for (auto& b : m_Buttons) {
        drawSprite(b.m_texture,
                   b.button_rect.x + g_text_padding,
                   b.button_rect.y + g_text_padding);
    }

    return false;
}

void MenuState::GenerateButtons() {
    std::map<int, std::string> labels = {
        {StartButton, "New Game"},
        {ScoreButton, "Leaderboard"},
        {ExitButton, "Exit"}
    };

    for (int i = 0; i < CountButton; ++i) {
        m_Buttons[i] = GenerateButton(labels[i].c_str());
    }

    AlignButtons();
}

Button MenuState::GenerateButton(const char *text) {
    Button b;

    b.m_texture = generateTextTexture(text, g_menu_label_size, label_color, &b.texture_w, &b.texture_h);

    return b;
}

void MenuState::AlignButtons() {
    int texture_h = m_Buttons[0].texture_h;
    int total_height_of_labels = CountButton * (texture_h + (2 * g_text_padding));
    int top_padding = (m_s->m_window_h - total_height_of_labels) / 2;

    for (int i = 0; i < CountButton; ++i) {
        int texture_w = m_Buttons[i].texture_w;
        int side_padding = (m_s->m_window_w - (texture_w + (2 * g_text_padding))) / 2;

        m_Buttons[i].button_rect = {side_padding,
                                    top_padding + ((texture_h + g_text_padding) * i),
                                    texture_w + (2 * g_text_padding),
                                    texture_h + (2 * g_text_padding)};
    }
}
