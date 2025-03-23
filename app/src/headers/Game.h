#pragma once
#include "Sdl.h"

class Game {
public:
    Game(int windowWidth, int windowHeight)
        : m_world(windowWidth, windowHeight)
        , m_sdl(*this, windowWidth, windowHeight) {}

    int start();

    // used in Events class to create object dynamicly
    ObjectPtr createRect(float x, float y, float mass, float width, float height, SDL_Color color);
    // event functions
    void deleteAllObjects();
    // used in Events to move objects
    void moveObject(ObjectPtr object, Vector2 amount);
    void moveObjectTo(ObjectPtr object, Vector2 position);
    void stopObject(ObjectPtr object);

private:
    void loopCount();

    Sdl m_sdl;
    PhysicsWorld m_world;
};
