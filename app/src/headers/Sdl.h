#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "Events.h"
#include "Renderer.h"

class Sdl {
public:
    Sdl(Game& game, int windowWidth, int windowHeight)
        : renderer(windowWidth, windowHeight)
        , event(*this, game) {}

    // creating and destroying windows and renderers
    void kill();

    // interfaces:
    Events event;
    Renderer renderer;

private:
};
