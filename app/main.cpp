#include "snake.h"

#include <iostream>
#include <algorithm>

void PrintError() noexcept {
    std::cout << "usage: ./race00 [width] [height]. Width and height must be valid integers."
              << std::endl << "Width ∈ [300, 800], heigt ∈ [300, 750]." << std::endl;
}

bool ParseArguments(int argc, char *argv[], int& w, int &h) {
    if (argc != 3) {
        std::cout << "usage: ./race00 [width] [height]" << std::endl;
        return false;
    }

    std::string str_w = argv[1], str_h = argv[2];
    auto predicate = [](char c) {return !std::isdigit(c);};
    if (std::find_if(str_w.begin(), str_w.end(), predicate) != str_w.end() ||
        std::find_if(str_h.begin(), str_h.end(), predicate) != str_h.end()) {
        PrintError();
        return false;
    }

    w = std::stoi(str_w);
    h = std::stoi(str_h);

    if (w < 300 || w > 800 || h < 300 || h > 750) {
        PrintError();
        return false;
    }

    return true;
}

int main(int argc, char *argv[]) {
    int w, h;

    if (!ParseArguments(argc, argv, w, h))
        return -1;

    return run(new Snake(w, h));
}