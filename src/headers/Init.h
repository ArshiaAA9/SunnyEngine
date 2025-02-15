#pragma once

#include "Physics.h"
#include "ObjectHandler.h"
#include "GridPartition.h"

class Init {
private:

ObjectHandler m_handler;
GridPartition m_grid;

public:

    Init(PhysicsWorld& world, float width, float height) : m_handler(world), m_grid(width, height) {}

    ObjectHandler& getObjectHandler(){
        return m_handler;
    }


};