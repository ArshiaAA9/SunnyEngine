#include "headers/Physics.h"

void PhysicsWorld::dynamicsUpdate(float dt) {
    for (auto& obj : Handler.getObjects()) {
        obj->force += m_gravity * obj->mass; // apply a force
        obj->velocity += obj->force / obj->mass * dt;
        obj->transform.position += obj->velocity * dt;
        obj->force = Vector2(0, 0); // reset net force at the end
    }
}

void PhysicsWorld::step(float dt) {
    // updates the simulation every dt
    dynamicsUpdate(dt);
}

void PhysicsWorld::setGravity(Vector2 gravity) { m_gravity = gravity; }
