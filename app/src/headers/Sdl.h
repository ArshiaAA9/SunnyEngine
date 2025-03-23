#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include "Events.h"
#include "Renderer.h"

class Sdl {
public:
    Sdl(Game& game, int windowWidth, int windowHeight)
        : renderer(windowWidth, windowHeight)
        , event(*this, game) {}

    // interfaces:
    Events event;
    Renderer renderer;

private:
};
