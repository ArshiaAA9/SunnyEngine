#include <SDL3/SDL.h>

#include "Game.h"

int main(int argc, char** argv) {
    // initialize the game
    Game game(1000, 484);
    game.start();
}
