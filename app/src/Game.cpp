#include "headers/Game.h"

#include <iostream>

#include "headers/Events.h"
#include "headers/Sdl.h"

// simulation itself
int Game::start() {

    int dt = 1.0f;
    Object* circle1 = m_world.Handler.createCircleObj(200, 200, 1, 10);
    Object* circle2 = m_world.Handler.createCircleObj(202, 200, 1, 10);

    m_world.cD.m_grid.updateCellDimensions();
    int count = 0;

    while (m_sdl.event.loop()) {
        std::cout << "loop count: " << count << std::endl;
        count++;
        m_world.step(dt);
        SDL_Delay(1000);
    }
    m_sdl.kill();
    return 0;
}
