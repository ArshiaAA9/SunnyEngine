#include "headers/Physics.h"

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
        obj->force += m_gravity * obj->mass; // apply a force
        obj->velocity += obj->force / obj->mass * dt;
        obj->transform.position += obj->velocity * dt;
        obj->force = Vector2(0, 0); // reset net force at the end
    }
}

void PhysicsWorld::setGravity(Vector2 gravity) { m_gravity = gravity; }

void PhysicsWorld::invertGravity() { m_gravity.invert(); }
