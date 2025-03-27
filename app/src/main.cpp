#include <SDL3/SDL.h>

#include <unordered_set>

#include "headers/Game.h"

int main(int argc, char** argv) {
    std::unordered_set<std::string> flags;
    for (int i = 1; i < argc; i++) {
        flags.insert(argv[i]);
    }

    // initialize the game
    Game game(1000, 500);

    if (flags.count("--test") || flags.count("-t")) {
        // test flag
        game.test();

    } else {
        // no flags
        game.start();
    }
}
