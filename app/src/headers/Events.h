#pragma once

#include <SDL2/SDL_events.h>

class Game;
class PhysicsWorld;
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
    void createRectOnMousePos(int mx, int my, float m, float width, float height);

    Game& m_game;
    SDL_Event m_sdlEvent;
    Sdl& m_sdl;
};
