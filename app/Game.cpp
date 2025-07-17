#include "Game.h"

#include <Physics.h>

#include <iostream>
#include <vector>

#include "Events.h"
#include "Sdl.h"

using namespace SE;

int Game::start() {
    m_world.setGravity(Vector2(0, 0));
    float dt = 1.0f / 60.0f;
    float delay = 1000.0f / 60.0f;
    ObjectPtr rect1;
    ObjectPtr rect2;
    ObjectPtr circle;

    SDL_FColor circleColor = {0, 0, 255, 255};
    SDL_FColor rectColor = {0, 255, 0, 255};
    SDL_FColor staticCircleColor = {255, 0, 0, 255};
    SDL_FColor staticObjectColor = {0, 0, 255, 255};
    float angle = 0;

    rect1 = createRect(250, 250, 1, 50, 50, rectColor, angle, 1.0f);
    circle = createCircle(300, 150, 3, 40, circleColor, angle, 0.8f);

    createStaticCircle(100, 100, 35, staticCircleColor, angle);
    createStaticCircle(700, 400, 25, staticCircleColor, angle);
    createStaticCircle(900, 130, 30, staticCircleColor, angle);

    createStaticRect(5, 243, 10, 479.9, staticObjectColor, angle);
    createStaticRect(995, 243, 10, 479.9, staticObjectColor, angle);
    createStaticRect(500, 5, 1000, 10, staticObjectColor, angle);

    // FIX:FIX GRID TO MAKE THIS COLLIDE
    createStaticRect(500, 478.9, 1000, 10, staticObjectColor, 0);

    setMainObject(rect1);
    m_world.cD.grid.updateCellDimensions();

    // main loop
    while (m_sdl.event.loop()) {
        // loopCount();
        m_world.step(dt);
        m_sdl.renderer.update(m_world);
        SDL_Delay(delay);
    }
    return 0;
}

// test function
void Game::rotateObject(ObjectPtr object, float amount) {
    // std::cout << "position: " << object->transform.position << " angle: " <<
    // object->transform.angle << '\n'; object->transform.printVertices();
    object->transform.increaseAngle(amount);
    // std::cout << "angle: " << object->transform.angle << "\n";
    object->transform.transform();
    // object->transform.printVertices();
}

void Game::loopCount() {
    static int count = 1;
    std::cout << "loop count: " << count << std::endl;
    count++;
}

void Game::setMainObject(ObjectPtr object) { m_mainObject = object; }

ObjectPtr Game::getMainObject() { return m_mainObject; }

void Game::moveObject(ObjectPtr object, Vector2 amount) { object->applyForce(amount); }

void Game::moveObjectTo(ObjectPtr object, Vector2 position) { object->transform.moveTo(position); }

void Game::stopObject(ObjectPtr object) { object->setVelocity(Vector2(0, 0)); }

ObjectPtr
Game::createRect(float x, float y, float mass, float width, float height, SDL_FColor color, float angle, float cof) {
    ObjectPtr pObject = m_world.handler.createRectObj(x, y, mass, width, height);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}

ObjectPtr
Game::createStaticRect(float x, float y, float width, float height, SDL_FColor color, float angle, float cof) {
    ObjectPtr pObject = m_world.handler.createStaticRect(x, y, width, height);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}

ObjectPtr Game::createCircle(float x, float y, float mass, float radius, SDL_FColor color, float angle, float cof) {
    ObjectPtr pObject = m_world.handler.createCircleObj(x, y, mass, radius);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}

ObjectPtr Game::createStaticCircle(float x, float y, float radius, SDL_FColor color, float angle, float cof) {
    ObjectPtr pObject = m_world.handler.createStaticCircle(x, y, radius);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}

// NOTE:: can be optimized for performance
void Game::deleteAllObjects() {
    auto renderMap = m_sdl.renderer.getRenderMap(); // copy all objects
    std::vector<ObjectPtr> tempVector;              // NOTE: can play with this for performance
    tempVector.resize(renderMap.size());
    for (const auto& [obj, color] : renderMap) {
        if (obj == m_mainObject) continue;
        tempVector.push_back(obj); // add them to temporarly vector
    }

    // Delete each object and remove from render map
    for (ObjectPtr obj : tempVector) {
        try {
            m_world.handler.deleteObject(obj);    // Delete from the world
            m_sdl.renderer.deleteRenderPair(obj); // Remove from render map
        } catch (const std::exception& e) {
            std::cerr << "Error deleting object " << obj << ": " << e.what() << "\n";
        }
    }
}
