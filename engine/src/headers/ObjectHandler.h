#pragma once

#include <memory>

#include "Objects.h"
#include "Types.h"
#include "Vector2.h"
class PhysicsWorld;

class ObjectHandler {
public:
    ObjectHandler(PhysicsWorld& world)
        : m_world(world) {}

    // returns object vector
    const std::vector<ObjectPtr>& getObjects() const;

    // methods for creating objects
    ObjectPtr createRectObj(float x, float y, float mass, float width, float height);
    ObjectPtr createCircleObj(float x, float y, float mass, float radius);

    // use this to delete an object
    void deleteObject(ObjectPtr object);

private:
    PhysicsWorld& m_world;
    std::vector<ObjectPtr> m_objects;

    // method for adding objects used inside createObject functions
    void addObject(ObjectPtr object);
};
