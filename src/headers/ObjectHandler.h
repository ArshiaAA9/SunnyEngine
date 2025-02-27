#pragma once

#include "Objects.h"
#include "Vector2.h"
#include "GridPartition.h"

class ObjectHandler {
private:

    PhysicsWorld& world;
    
    ObjectHandler(PhysicsWorld& world) : world(world) {}

    friend class Init;

public:

    RectObject* rectCreate(float x, float y, float mass, float width, float height);
    CircleObject* circleCreate(float x, float y, float mass, float radius);

};