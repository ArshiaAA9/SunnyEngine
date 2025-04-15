#include "headers/Physics.h"

#include <iostream>

namespace SE {

// public:
void PhysicsWorld::step(float dt) {
    // updates objects inside each cell at start of each frame
    cD.m_grid.updateCells();
    // check for collisions
    cD.checkCollisions();
    // solve the collisions
    m_solver.solveCollisionPairs();
    // updates the simulation
    dynamicsUpdate(dt);
}

// privates:
void PhysicsWorld::dynamicsUpdate(float dt) {
    for (auto& obj : Handler.getObjects()) {
        obj->applyForce(m_gravity * obj->mass);
        obj->addVelocity(obj->force / obj->mass * dt);
        obj->transform.move(obj->velocity * dt);
        obj->transform.transform();
        obj->force = Vector2(0, 0); // reset net force at the end
    }
}

void PhysicsWorld::setGravity(Vector2 gravity) { m_gravity = gravity; }

void PhysicsWorld::invertGravity() { m_gravity.invert(); }
} // namespace SE
