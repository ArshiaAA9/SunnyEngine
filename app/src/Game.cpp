#include "headers/Game.h"

#include <iostream>

#include "headers/Events.h"
#include "headers/Sdl.h"

// simulation itself
int Game::start() {
    m_world.setGravity(Vector2(0, 0));
    float dt = 1.0f / 60.0f;
    float delay = 1000.0f / 60.0f;
    Object* rect1 = m_world.Handler.createRectObj(100, 250, 100, 100, 100);
    Object* rect2 = m_world.Handler.createRectObj(100, 250, 1, 10, 10);

    m_world.cD.m_grid.updateCellDimensions();
    int count = 0;

    while (m_sdl.event.loop()) {
        std::cout << "loop count: " << count << std::endl;
        count++;
        m_world.step(dt);
        m_sdl.renderer.clearScreen();
        m_sdl.renderer.drawColoredRect(*rect1, 0, 126, 0, 1);
        m_sdl.renderer.drawColoredRect(*rect2, 163, 0, 0, 1);
        m_sdl.renderer.update();
        SDL_Delay(delay);
    }
    m_sdl.kill();
    return 0;
}
