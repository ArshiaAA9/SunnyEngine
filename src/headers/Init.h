#pragma once

#include "Physics.h"
#include "ObjectHandler.h"
#include "GridPartition.h"
#include "CollisionDetection.h"

class Init {
private:

ObjectHandler m_handler;
GridPartition m_grid;
CollisionDetection m_collisionDetection;

public:

    Init(PhysicsWorld& world, float width, float height) 
    : m_handler(world)
    , m_grid(width, height)
    , m_collisionDetection(){}

    ObjectHandler& getObjectHandler(){
        return m_handler;
    }

    CollisionDetection& getCollisionDetection(){
        return m_collisionDetection;
    }
};