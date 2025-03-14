#include <SDL2/SDL.h>
#include <unistd.h>

#include <iostream>

#include "headers/Physics.h"

int main(int argc, char** args) {
    PhysicsWorld world(1000, 500);

    Object* circle1 = world.Handler.createCircleObj(200, 200, 1, 10);
    Object* circle2 = world.Handler.createCircleObj(202, 200, 1, 10);

    bool running;
    int dt = 1.0f;

    world.cD.m_grid.updateCellDimensions();

    for (int i = 0; i < 5; i++) {
        world.step(dt);
    }
    return 0;
}
