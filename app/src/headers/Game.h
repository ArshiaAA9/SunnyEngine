#pragma once
#include "../../../engine/src/headers/Physics.h"
#include "Sdl.h"

class Game {
public:
    Game(int windowWidth, int windowHeight)
        : m_sdl(windowWidth, windowHeight)
        , m_world(windowWidth, windowHeight) {}

    int start();

private:
    Sdl m_sdl;
    PhysicsWorld m_world;
};
