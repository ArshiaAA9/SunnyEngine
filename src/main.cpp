#include <SDL2/SDL.h>
#include <unistd.h>

#include <iostream>

#include "headers/Physics.h"

int main(int argc, char** args) {
    PhysicsWorld world(1000, 500);
    Object* circle1 = world.Handler.createCircleObj(200, 200, 1, 5);
    circle1->printProperties();

    return 0;
}
