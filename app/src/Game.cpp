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

    m_world.cD.m_grid.updateCellDimensions(); // FIX:THIS IS WHY THE RIGHT HALF DOESNT WORK

    // main loop
    while (m_sdl.event.loop(rect1)) {
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

void Game::moveObject(ObjectPtr object, Vector2 amount) {
    object->applyForce(amount);
    std::cout << amount.x << ',' << amount.y << '\n';
}

void Game::stopObject(ObjectPtr object) { object->setVelocity(Vector2(0, 0)); }

ObjectPtr Game::createRect(float x, float y, float mass, float width, float height, SDL_Color color) {
    ObjectPtr pObject = m_world.Handler.createRectObj(x, y, mass, width, height);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}

// FIX:: MEMORY LEAK
void Game::deleteAllObjects() {
    // Delete objects and remove them from the render map
    for (auto& [obj, color] : m_sdl.renderer.getRenderMap()) {
        try {
            m_world.Handler.deleteObject(obj);    // delete object from world
            m_sdl.renderer.deleteRenderPair(obj); // Remove from renderMap
        } catch (const std::exception& e) {
            std::cerr << "Error deleting object " << obj << ": " << e.what() << "\n";
        } catch (...) {
            std::cerr << "Unknown error deleting object " << obj << "\n";
        }
        std::cout << "something";
    }
}
