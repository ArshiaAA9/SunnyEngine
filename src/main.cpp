#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "headers/Physics.h"
#include "headers/ObjectHandler.h"
#include "headers/Init.h"



int main(int argc, char** args){
    PhysicsWorld world;

    Init init(world);
    ObjectHandler objectHandler = init.getObjectHandler();

    world.setGravity(Vector2(1,0));

    RectObject* rect = objectHandler.rectCreate(0, 0, 1, 1, 1);

    rect->velocity = Vector2(0, -10);
    rect->applyForce(Vector2(5, 0));

    rect->printProperties();
    return 0;
}

