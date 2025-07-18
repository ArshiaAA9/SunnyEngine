#pragma once

#include <SDL3/SDL_events.h>

class Game;
class Sdl;

class Events {
public:
    Events(Sdl& sdl, Game& game)
        : m_sdl(sdl)
        , m_game(game) {}

    // main event loop with PollEvent()
    bool loop();

    SDL_Event& getEventVar();

private:
    // these functions are used in loop inside the switch cases
    void keydownEvents();
    void mouseButtonUpEvents();

    // game related functions:
    void
    createRectOnMousePos(float mx, float my, float m, float width, float height, SDL_FColor color = {255, 0, 0, 1});
    void deleteAllObjects();

    Game& m_game;
    SDL_Event m_sdlEvent;
    Sdl& m_sdl;
};
