#pragma once

#include <SDL2/SDL_events.h>

class Sdl;

class Events {
public:
    Events() = default;

    bool loop();

    SDL_Event& getEventVar();

private:
    SDL_Event m_sdlEvent;
};
