#pragma once

#include <memory>
#include <vector>

#include "CollisionPair.h"
#include "GridPartition.h"
#include "Objects.h"

class GridPartition;
class PhysicsWorld;

class CollisionDetection {
public:
    CollisionDetection(float gridHeight, float gridWidth, PhysicsWorld& world)
        : m_grid(gridHeight, gridWidth, world) {}

    // collision detection inerface:
    void checkCollisions();

    // returns a pointer to collisionpair vector
    const std::vector<std::unique_ptr<CollisionPair>>& getClPairs() const;

    void addClPair(Object* obj1, Vector2 pointA, Object* obj2, Vector2 pointB, float depth);
    void deleteClPair(CollisionPair* pair);

    GridPartition m_grid;

private:
    std::vector<std::unique_ptr<CollisionPair>> m_collisionPairs;

    void checkCollisionByType(Object* obj1, Object* obj2);

    void clCircleCircle(Object* obj1, Object* obj2);

    void clCircleRect(Object* obj1, Object* obj2);

    bool aabb(Object* obj1, Object* obj2);

    void clRectRect(Object* obj1, Object* obj2);
};
