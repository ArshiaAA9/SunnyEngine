#pragma once
#include "CollisionPair.h"
#include "Vector2.h"

namespace SE {
class PhysicsWorld;

class Solver {
public:
    Solver(PhysicsWorld& world)
        : m_world(world) {}

    void solveCollisionPairs();

private:
    PhysicsWorld& m_world;
    float calculateRelativeVelocity(CollisionPair* pair);      // used in calculate impulse
    Vector2 calculateImpulse(CollisionPair* pair, float vrel); // used in apply impulse to calculate impulse
    void applyImpulse(CollisionPair* pair, Vector2 impulse);   // applies force to the object pair
    void solve(CollisionPair* pair);
};
} // namespace SE
