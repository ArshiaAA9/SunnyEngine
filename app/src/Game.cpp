#include "headers/Game.h"

#include <iostream>

#include "headers/Events.h"
#include "headers/Sdl.h"

// TODO: ADD ROTATION
//  simulation itself
int Game::start() {
    m_world.setGravity(Vector2(0, -0));
    float dt = 1.0f / 60.0f;
    float delay = 1000.0f / 60.0f;
    ObjectPtr rect1;
    ObjectPtr rect2;
    SDL_Color color = {0, 255, 0, 255};
    rect1 = createRect(100, 250, 1, 100, 100, color);
    rect2 = createRect(200.5, 250, 1, 100, 100, color);

    setMainObject(rect1);

    // main loop
    while (m_sdl.event.loop()) {
        m_world.cD.m_grid.updateCellDimensions(); // FIX:THIS IS WHY THE RIGHT HALF DOESNT WORK
        m_world.step(dt);
        m_sdl.renderer.update(m_world);
        SDL_Delay(delay);
    }
    // clean up
    m_sdl.kill();
    return 0;
}

void Game::loopCount() {
    static int count = 1;
    std::cout << "loop count: " << count << std::endl;
    count++;
}

void Game::setMainObject(ObjectPtr object) { m_mainObject = object; }

ObjectPtr Game::getMainObject() { return m_mainObject; }

void Game::moveObject(ObjectPtr object, Vector2 amount) {
    object->applyForce(amount);
    std::cout << amount.x << ',' << amount.y << '\n';
}

void Game::moveObjectTo(ObjectPtr object, Vector2 position) { object->transform.moveTo(position); }

void Game::stopObject(ObjectPtr object) { object->setVelocity(Vector2(0, 0)); }

ObjectPtr Game::createRect(float x, float y, float mass, float width, float height, SDL_Color color) {
    ObjectPtr pObject = m_world.Handler.createRectObj(x, y, mass, width, height);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}

// FIX:: throws segfault error
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
