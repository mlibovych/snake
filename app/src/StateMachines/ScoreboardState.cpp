#include <iostream>

#include "ScoreboardState.h"
#include "../snake.h"

void ScoreboardState::Init() {

}


void ScoreboardState::Enter() {
    std::filesystem::file_time_type new_last_write_time;

    try {
        new_last_write_time = std::filesystem::last_write_time("./app/resources/.leaderboard");
    }
    catch (std::filesystem::filesystem_error& e) {
        std::ofstream new_file("./app/resources/.leaderboard");
        new_file.close();
        std::ifstream file("./app/resources/.leaderboard");
        UpdateLeaderboard(file);
        file.close();

        try {
            m_last_write_time = std::filesystem::last_write_time("./app/resources/.leaderboard");
        }
        catch (std::filesystem::filesystem_error &e) {
            std::cerr << "Some weird shit is going on with the filesystem! Leaderboard will remain empty. Try to go back to menu and into the leaderboard again. It may or may not help. Sorry bro";
        }

        return;
    }
 
    if (m_last_write_time != new_last_write_time) {
        std::ifstream file("./app/resources/.leaderboard");

        if (file.is_open()) {
            UpdateLeaderboard(file);
            m_last_write_time = new_last_write_time;
            file.close();
        }
        else {
            std::cerr << "Some weird shit is going on with the filesystem! Leaderboard will remain empty. Try to go back to menu and into the leaderboard again. It may or may not help. Sorry bro";
        }
    }
}

States ScoreboardState::HandleInput(FRKey k) {
    return Scoreboard;
}

bool ScoreboardState::Tick() {
    return false;
}

void ScoreboardState::UpdateLeaderboard(std::istream& file) {
    int i = 0;
    std::string line;

    while (std::getline(file, line) && i < 10) {
        Score score;
        auto pos = line.find(' ');

        if (pos == std::string::npos) {
            score.name = "????????";
            score.points = "-1";
            m_Leaders[i++] = score;
        }

        score.name = std::string(line.begin(), line.begin() + pos);
        
        std::string points = std::string(line.begin() + pos + 1, line.end());
        auto pred = [](char c) {return !std::isdigit(c);};

        if (std::find_if(points.begin(), points.end(), pred) != points.end()) {
            points = "-1";
        }
        else {
            try {
                std::stoi(points);
                score.points = points;
            }
            catch (std::invalid_argument& e) {
                score.points = "-1";
            }
            catch (std::out_of_range& e) {
                score.points = "-1";
            }
        }

        m_Leaders[i] = score;
        CreateTextTexture(i);
        // std::cout << score.name << " " << score.points << std::endl;

        ++i;
    }

    while (i < 10) {
        m_Leaders[i] = {"........", "....."};
        CreateTextTexture(i++);
    }
}

void ScoreboardState::CreateTextTexture(int i) {
    Score& score = m_Leaders[i];
    std::string line;

    line += std::to_string(i + 1) + ". ";

    if (i != 9)
        line += ' ';

    line += score.name;
    std::cout << max_name_len << " " << score.name.size() << " " << dots_between << " " << std::endl;
    line += std::string(max_name_len - score.name.size() + dots_between, '.');

    line += score.points;

    std::cout << line << " " << line.size() << std::endl;
    score.m_texture = generateTextTexture(line.c_str(), 20, label_color, &score.tex_w, &score.tex_h);
}
