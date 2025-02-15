#pragma once

#include "Objects.h"
#include "Vector2.h"
#include "GridPartition.h"

class ObjectHandler {
private:

    PhysicsWorld& world;
    GridPartition& grid;
    
    ObjectHandler(PhysicsWorld& world, GridPartition) : world(world), GridPartition(gird) {}

    friend class Init;

public:

    // Factory method to create a rectangle
    RectObject* rectCreate(float x, float y, float mass, float width, float height);
    CircleObject* circleCreate(float x, float y, float mass, float radius);

};