#pragma once

#include "Physics.h"
#include "ObjectHandler.h"


class Init {
private:

ObjectHandler m_handler;

public:

    Init(PhysicsWorld& world) : m_handler(world) {}

    ObjectHandler& getObjectHandler(){
        return m_handler;
    }


};