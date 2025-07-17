#pragma once

#include "Types.h"

namespace SE {
class PhysicsWorld;

class ObjectHandler {
public:
    ObjectHandler(PhysicsWorld& world)
        : m_world(world) {}

    // returns object vector
    const std::vector<ObjectPtr>& getObjects() const;

    // methods for creating objects
    ObjectPtr createRectObj(float x, float y, float mass, float width, float height);
    ObjectPtr createStaticRect(float x, float y, float width, float height);
    ObjectPtr createCircleObj(float x, float y, float mass, float radius);
    ObjectPtr createStaticCircle(float x, float y, float radius);

    // use this to delete an object
    void deleteObject(ObjectPtr object);

private:
    PhysicsWorld& m_world;
    std::vector<ObjectPtr> m_objects;

    // method for adding objects used inside createObject functions
    void addObject(ObjectPtr object);
};
} // namespace SE
