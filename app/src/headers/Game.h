#pragma once
#include "Sdl.h"

class Game {
public:
    Game(int windowWidth, int windowHeight)
        : m_world(windowWidth, windowHeight)
        , m_sdl(*this, windowWidth, windowHeight) {}

    int start();

    // used in Events class to create object dynamicly
    const Object*
    createRect(float x, float y, float mass, float width, float height, SDL_Color color);

private:
    void loopCount();

    Sdl m_sdl;
    PhysicsWorld m_world;
};
