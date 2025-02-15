#pragma once

#include "Physics.h"
#include "ObjectHandler.h"
#include "GridPartition.h"

class Init {
private:

ObjectHandler m_handler;

public:

    Init(PhysicsWorld& world, GridPartition grid) : m_handler(world, grid) {}

    ObjectHandler& getObjectHandler(){
        return m_handler;
    }


};