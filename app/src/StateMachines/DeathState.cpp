#include "DeathState.h"
#include "../snake.h"

void DeathState::Init() {
    int text_size_letters = 30;

    if (m_s->m_window_h >= 500 && m_s->m_window_h >= 500) {
        text_size_letters = 50;
        m_text_size_labels = 60;
    }

    for (char c = 97; c <= 122; ++c) {
        Button b;
        char *str = new char[2];
        str[0] = c;
        str[1] = '\0';
        Sprite *s = generateTextTexture(str, text_size_letters, label_color,
                                        &b.texture_w, &b.texture_h);
        delete[] str;
        b.m_texture = s;

        m_letters[c] = b;
        m_label1.m_texture = nullptr;
        m_label2.m_texture = nullptr;
    }

    m_input_rect.h = m_letters['a'].texture_h + (2 * text_padding);
    m_input_rect.w = (m_letters['a'].texture_w * max_name_len) + (2 * text_padding);
    m_input_rect.x = m_s->AlignHorizontally(m_input_rect.w, 0);
}

void DeathState::Enter() {
    if (m_label1.m_texture)
        delete m_label1.m_texture;
    if (m_label2.m_texture)
        delete m_label2.m_texture;

    std::string text1 = "Your score is ";
    // text += std::to_string(m_s->m_score);
    text1 += "123";
    std::string text2 = "Please enter your name:";

    m_label1.m_texture = generateTextTexture(text1.c_str(), m_text_size_labels,
                                            label_color, &m_label1.texture_w, &m_label1.texture_h);

    m_label2.m_texture = generateTextTexture(text2.c_str(), m_text_size_labels,
                                            label_color, &m_label2.texture_w, &m_label2.texture_h);

    m_label1.button_rect.x = m_s->AlignHorizontally(m_label1.texture_w, 0);
    m_label2.button_rect.x = m_s->AlignHorizontally(m_label2.texture_w, 0);
    m_input_rect.y = text_padding + m_label1.texture_h + text_padding + m_label2.texture_h + text_padding;
}

States DeathState::HandleInput(FRKey k) {
    if (k == FRKey::ENTER && m_username.size() >= 1) {
        // SaveScore();
        return Scoreboard;
    }
    return Death;
}

States DeathState::HandleInput(int32_t k) {
    std::cout << char(k) << std::endl;
    return Death;
}

States DeathState::Tick() {
    drawSprite(m_label1.m_texture, m_label1.button_rect.x, text_padding);
    drawSprite(m_label2.m_texture, m_label2.button_rect.x, text_padding + m_label1.texture_h + text_padding);
    drawRect(m_input_rect.w, m_input_rect.h, m_input_rect.x, m_input_rect.y, {114, 125, 107});
    return Death;
}

