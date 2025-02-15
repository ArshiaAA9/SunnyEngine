#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "Vector2.h"
#include "Objects.h"

struct Object;

class PhysicsWorld {
private:

    std::vector<Object*> m_objects;
    Vector2 m_gravity = Vector2(0, -9.81);

public:

    void addObject(Object* object);
    void removeObject(Object* object);

    std::vector<Object*> getObjects();

    void step(float dt);


    void setGravity(Vector2 gravity);
};





