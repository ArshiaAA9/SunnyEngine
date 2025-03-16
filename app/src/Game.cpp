#include "headers/Game.h"

#include <iostream>

#include "headers/Events.h"
#include "headers/Sdl.h"

// TODO: ADD ROTATION
//  simulation itself
int Game::start() {
    m_world.setGravity(Vector2(0, -20));
    float dt = 1.0f / 60.0f;
    float delay = 1000.0f / 60.0f;
    Object* rect1 = m_world.Handler.createRectObj(100, 250, 1, 100, 100);
    Object* rect2 = m_world.Handler.createRectObj(200.5, 250, 1, 100, 100);

    m_world.cD.m_grid.updateCellDimensions();

    while (m_sdl.event.loop()) {
        // loopCount();
        m_world.step(dt);
        m_sdl.renderer.update(m_world);
        SDL_Delay(delay);
    }
    m_sdl.kill();
    return 0;
}

void Game::loopCount() {
    static int count = 1;
    std::cout << "loop count: " << count << std::endl;
    count++;
}

const Object* Game::createRect(float x, float y, float mass, float width, float height, SDL_Color color) {
    const Object* pObject = m_world.Handler.createRectObj(x, y, mass, width, height);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}
