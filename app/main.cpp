#include "snake.h"

void ParseArguments(int argc, char *argv[], int& w, int &h) {
    w = 10;
    h = 10;
}

int main(int argc, char *argv[]) {
    int w, h;

    ParseArguments(argc, argv, w, h);

    return run(new Snake(w, h));
}