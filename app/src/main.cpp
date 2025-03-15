#include <SDL2/SDL.h>
#include <unistd.h>

#include "headers/Game.h"

int main(int argc, char** args) {
    Game game(1000, 500);
    game.start();
}
