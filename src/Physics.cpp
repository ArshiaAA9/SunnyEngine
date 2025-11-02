#include "Physics.h"

namespace SE {

// public:
void PhysicsWorld::step(float dt) {
    // updates objects inside each cell at start of each frame
    cD.grid.updateCells();
    // check for collisions
    cD.checkCollisions();
    // solve the collisions
    m_solver.solveCollisionPairs();
    // updates the simulation
    dynamicsUpdate(dt);
}

// privates:
void PhysicsWorld::dynamicsUpdate(float dt) {
    for (auto& obj : handler.getObjects()) {
        if (!obj->isStatic()) {
            float objMass = obj->getMass();
            obj->applyForce(m_gravity * objMass);
            obj->addVelocity(obj->force * obj->getInvertedMass() * dt);

            // angular velocity related:
            obj->addAngularVelocity(obj->torque * obj->getInvertedInertia() * dt);
            obj->transform.increaseAngle(obj->angularVelocity * dt);

            obj->transform.move(obj->velocity * dt);
            obj->force = Vector2(0, 0); // reset net force at the end
        }
        obj->transform.transform();
    }
}

void PhysicsWorld::setGravity(Vector2 gravity) { m_gravity = gravity; }

void PhysicsWorld::invertGravity() { m_gravity.invert(); }
} // namespace SE
