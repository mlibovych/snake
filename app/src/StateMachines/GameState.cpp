#include "GameState.h"

#include "Framework.h"
#include "../snake.h"

using namespace std::chrono;

States GameState::Tick() {
    uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    //draw field
    drawRect(m_s->m_playfield_w, m_s->m_playfield_h, 
                m_s->m_padding,
                m_s->m_padding + m_s->m_menu_height,
                {8,22,0});
    //food
    drawSprite(food.sprite, food.x, food.y);
    //growing
    if (now - hunger_time >= 4000) {
        hunger_time = now;
        snake.pop_back();
    }
    //move
    if (now - tick_time > speed) {
        tick_time = now;
        Move();
        if (CheckCollision()) {
            return Death;
        }
        //grow
        if (CheckCollision(snake.front(), food)) {
            hunger_time = now;
            Grow();
            SpawnFood();
            if (speed > 30) {
                speed -= 4;
            }
            m_s->score += 10;
        }
    }
    //draw snake
    for (const auto& piece : snake) {
        drawSprite(piece.sprite, piece.x, piece.y);
    }
    //check state
    if (snake.size() < 2) {
        return Death;
    }
    //score
    drawScore();
    return Game;
}

void GameState::drawScore() {
    int score = m_s->score;
    int x, y;
    std::deque<Sprite*> score_sprites;

    x = y = m_s->m_padding;
    if (!score) {
        drawSprite(numbers[score], x, y);
        return;
    }
    while (score) {
        score_sprites.push_front(numbers[score % 10]);
        score /= 10;
    }
    for (const auto& sprite : score_sprites) {
        drawSprite(sprite, x, y);
        x += score_w;
    }
}

States GameState::HandleInput(FRKey k) {
    Direction& direction = snake.front().direction;
    if (direction == Direction::UP ||
        direction == Direction::DOWN) {
        switch (k) {
        case FRKey::LEFT:
            head_direction = Direction::LEFT;
            break;
        case FRKey::RIGHT:
            head_direction = Direction::RIGHT;
            break;
        default:
            break;
        }
    }
    else if (direction == Direction::RIGHT ||
            direction == Direction::LEFT) {
        switch (k) {
        case FRKey::DOWN:
            head_direction = Direction::DOWN;
            break;
        case FRKey::UP:
            head_direction = Direction::UP;
            break;
        default:
            break;
        }
    }
    return Game;
}

void GameState::Load() {
    int snake_x, snake_y;

    snake_x = m_s->m_playfield_w / 2;
    snake_y = m_s->m_playfield_h / 2;
    snake_x -= snake_x % cell_width;
    snake_x += m_s->m_padding;
    snake_y -= snake_y % cell_width;
    snake_y += m_s->m_padding + m_s->m_menu_height;

    snake.clear();
    snake.push_back({createSprite("app/resources/head.png"),
                    snake_x,
                    snake_y,
                    Direction::UP});
    for (int i = 0; i < 3; ++i) {
        Grow();
    }

    SpawnFood();
    speed = 200;
    head_direction = Direction::UP;§
    m_s->score = 0;
}


void GameState::Init() {
    food.sprite = createSprite("app/resources/straw.png");

    for (int i = 0; i <= 9; i++) {
        numbers[i] = generateTextTexture(std::to_string(i).c_str(), 40, g_label_color,
            &score_w, &score_h);
    }
    Load();
}

bool GameState::CheckCollision(Piece& lhs, Piece& rhs) {
    int a_x0 = lhs.x;
    int a_y0 = lhs.y;
    int a_x1 = lhs.x + cell_width;
    int a_y1 = lhs.y + cell_width;

    int b_x0 = rhs.x;
    int b_y0 = rhs.y;
    int b_x1 = rhs.x + cell_width;
    int b_y1 = rhs.y + cell_width;

    if (a_x0 >= b_x1 || a_x1 <= b_x0 || a_y0 >= b_y1 || a_y1 <= b_y0) {
        return 0;
    }
    return 1;
}

bool GameState::CheckCollision() {
    int min_x = m_s->m_padding;
    int max_x = m_s->m_padding + m_s->m_playfield_w;
    int min_y = m_s->m_padding + m_s->m_menu_height;
    int max_y = m_s->m_padding + m_s->m_menu_height + m_s->m_playfield_h;
    bool head = true;

    if (snake.front().x < min_x || snake.front().x > max_x - cell_width ||
        snake.front().y < min_y || snake.front().y > max_y - cell_width) {
            return 1;
        }

    for (auto& piece : snake) {
        if (head) {
            head = false;
            continue;
        }
        if (CheckCollision(snake.front(), piece)) {
            return 1;
        }
    }
    return 0;
}

static int getRandomCoord(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    int res = dis(gen);
    res -= res % cell_width;

    return res;
}

void GameState::SpawnFood() {
    food.x = getRandomCoord(0, m_s->m_playfield_w - cell_width);
    food.y = getRandomCoord(0, m_s->m_playfield_h - cell_width);

    food.x += m_s->m_padding;
    food.y += m_s->m_padding + m_s->m_menu_height;
}

void GameState::Grow() noexcept {
    auto tail = snake.back();
    int x = tail.x;
    int y = tail.y;

    switch (tail.direction) {
    case Direction::UP:
        y += cell_width;
        break;
    case Direction::DOWN:
        y -= cell_width;
        break;
    case Direction::LEFT:
        x += cell_width;
        break;
    case Direction::RIGHT:
        x -= cell_width;
        break;
    default:
        break;
    }

    snake.push_back({createSprite("app/resources/body.png"),
                    x,
                    y,
                    tail.direction});
}

void GameState::Move() noexcept {
    Direction new_direction = snake.front().direction = head_direction;

    for (auto it = snake.begin(); it != snake.end(); it++) {
        Direction old_direction = it->direction;

        switch (it->direction) {
        case Direction::UP:
            it->y -= cell_width;
            break;
        case Direction::DOWN:
            it->y += cell_width;
            break;
        case Direction::LEFT:
            it->x -= cell_width;
            break;
        case Direction::RIGHT:
            it->x += cell_width;
            break;
        default:
            break;
        }
        it->direction = new_direction;
        new_direction = old_direction;
    };
}
