#pragma once
#include "../src/Physics.h"
#include "Sdl.h"

using namespace SE;

class Game {
public:
    Game(int windowWidth, int windowHeight)
        : m_world(windowWidth, windowHeight)
        , m_sdl(*this, windowWidth, windowHeight) {}

    int start();

    // used in Events class to create object dynamicly
    ObjectPtr
    createRect(float x, float y, float mass, float width, float height, SDL_FColor color, float angle, float cof = 1);
    ObjectPtr
    createStaticRect(float x, float y, float width, float height, SDL_FColor color, float angle, float cof = 1);
    ObjectPtr createCircle(float x, float y, float mass, float radius, SDL_FColor color, float angle, float cof = 1);
    ObjectPtr createStaticCircle(float x, float y, float radius, SDL_FColor color, float angle, float cof = 1);

    void setMainObject(ObjectPtr object);
    ObjectPtr getMainObject();

    // functions used in event.h
    void rotateObject(ObjectPtr object, float amount);
    void moveObject(ObjectPtr object, Vector2 amount);
    void moveObjectTo(ObjectPtr object, Vector2 position);
    void stopObject(ObjectPtr object);
    void spinObject(ObjectPtr object, float amout);
    void deleteAllObjects();

private:
    void loopCount();

    Sdl m_sdl;
    PhysicsWorld m_world;
    ObjectPtr m_mainObject;
};
