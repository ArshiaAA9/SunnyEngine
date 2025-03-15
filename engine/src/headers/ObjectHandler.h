#pragma once

#include <memory>

#include "Objects.h"
#include "Vector2.h"

class PhysicsWorld;

class ObjectHandler {
public:
    ObjectHandler(PhysicsWorld& world)
        : m_world(world) {}

    // returns object vector
    const std::vector<std::unique_ptr<Object>>& getObjects() const;

    // methods for creating objects
    Object* createRectObj(float x, float y, float mass, float width, float height);
    Object* createCircleObj(float x, float y, float mass, float radius);

private:
    PhysicsWorld& m_world;
    std::vector<std::unique_ptr<Object>> m_objects;

    // methods responsible for adding and deleting Objects
    void addObject(std::unique_ptr<Object>&& object);
    void deleteObject(Object* object);
};
