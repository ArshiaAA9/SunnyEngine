#include "headers/Game.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "headers/Events.h"
#include "headers/Sdl.h"

using namespace SE;

int Game::start() {
    m_world.setGravity(Vector2(0, -0));
    float dt = 1.0f / 60.0f;
    float delay = 1000.0f / 60.0f;
    ObjectPtr rect1;
    ObjectPtr rect2;
    SDL_FColor color = {0, 255, 0, 255};
    rect1 = createRect(100, 250, 1, 100, 100, color, 0);
    rect2 = createRect(250, 250, 900000000, 100, 100, color, 0);

    setMainObject(rect1);
    m_world.step(dt);
    rect1->transform.increaseAngle(M_PI / 4);
    rect2->transform.increaseAngle(M_PI / 4);

    // main loop
    while (m_sdl.event.loop()) {
        // loopCount();
        m_world.cD.m_grid.updateCellDimensions(); // FIX:THIS IS WHY THE RIGHT HALF DOESNT WORK
        m_world.step(dt);
        m_sdl.renderer.update(m_world);
        SDL_Delay(delay);
    }
    return 0;
}

int Game::test() {
    // m_world.setGravity(Vector2(0, -0));
    // float dt = 1.0f / 60.0f;
    float delay = 1000.0f / 60.0f;

    while (m_sdl.event.loop()) {
        loopCount();
        m_sdl.renderer.update(m_world);
        SDL_Delay(delay);
    }
    return 0;
}

// test function
void Game::rotateObject(ObjectPtr object, float amount) {
    // std::cout << "position: " << object->transform.position << " angle: " << object->transform.angle << '\n';
    // object->transform.printVertices();
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

ObjectPtr Game::createRect(float x, float y, float mass, float width, float height, SDL_FColor color, float angle) {
    ObjectPtr pObject = m_world.Handler.createRectObj(x, y, mass, width, height, angle);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}

// NOTE:: can be optimized for performance
void Game::deleteAllObjects() {
    auto renderMap = m_sdl.renderer.getRenderMap(); // copy all objects
    std::vector<ObjectPtr> tempVector;              // NOTE: can play with this for performance
    for (const auto& [obj, color] : renderMap) {
        if (obj == m_mainObject) continue;
        tempVector.push_back(obj); // add them to temporarly vector
    }

    // Delete each object and remove from render map
    for (ObjectPtr obj : tempVector) {
        try {
            m_world.Handler.deleteObject(obj);    // Delete from the world
            m_sdl.renderer.deleteRenderPair(obj); // Remove from render map
        } catch (const std::exception& e) {
            std::cerr << "Error deleting object " << obj << ": " << e.what() << "\n";
        }
    }
}
