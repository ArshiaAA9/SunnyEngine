#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "headers/Physics.h"
#include "headers/ObjectHandler.h"
#include "headers/Init.h"



int main(int argc, char** args){
    PhysicsWorld world;

    Init init(world, 1000, 500);

    ObjectHandler objectHandler = init.getObjectHandler();
    CollisionDetection cD = init.getCollisionDetection();

    // world.setGravity(Vector2(1,0));

    RectObject* rect1 = objectHandler.rectCreate(0, 0, 1, 1, 1);
    RectObject* rect2 = objectHandler.rectCreate(1, -1, 1, 1, 1);

    cD.clRectRect(*rect1, *rect2);
    std::cout << "\n";

    return 0;
}

