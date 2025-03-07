#pragma once

#include "Objects.h"
#include "Vector2.h"

class PhysicsWorld;

class ObjectHandler {
public:
    ObjectHandler(PhysicsWorld* world) : m_world(world) {}

    // methods responsible for adding and deleting Objects
    void addObject(Object* object);
    void deleteObject(Object* object);

    // returns object vector
    std::vector<Object*>* getObjects();

    Object* createRectObjptr(float x, float y, float mass, float width, float height);
    Object* createCircleObjptr(float x, float y, float mass, float radius);

private:
    PhysicsWorld* m_world;
    std::vector<Object*> m_objects;
};
