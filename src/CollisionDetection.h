#pragma once

#include <memory>
#include <vector>

#include "CollisionPair.h"
#include "GridPartition.h"
#include "Types.h"

namespace SE {
class GridPartition;
class PhysicsWorld;

class CollisionDetection {
public:
    CollisionDetection(float gridHeight, float gridWidth, PhysicsWorld& world)
        : grid(gridHeight, gridWidth, world) {}

    // collision detection inerface:
    void checkCollisions();

    // returns a pointer to collisionpair vector
    const std::vector<std::unique_ptr<CollisionPair>>& getClPairs() const;

    void addClPair(ObjectPtr obj1, Vector2 pointA, ObjectPtr obj2, Vector2 pointB, float depth, Vector2 normal);
    void deleteClPair(CollisionPair* pair);

    GridPartition grid;

private:
    std::vector<std::unique_ptr<CollisionPair>> m_collisionPairs;

    void checkCollisionByType(ObjectPtr obj1, ObjectPtr obj2);

    void clCircleCircle(ObjectPtr c1, ObjectPtr c2);

    void clCircleRect(ObjectPtr obj1, ObjectPtr obj2);

    void aabb(ObjectPtr obj1, ObjectPtr obj2);
    void sat(ObjectPtr obj1, ObjectPtr obj2);
    Vector2 satProject(std::vector<Vector2>& vertices, Vector2 axis);
};
} // namespace SE
