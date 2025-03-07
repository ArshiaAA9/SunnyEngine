#pragma once

#include <vector>

#include "CollisionPair.h"
#include "GridPartition.h"
#include "Objects.h"

class GridPartition;
class PhysicsWorld;

class CollisionDetection {
public:
    CollisionDetection(GridPartition* grid)
        : m_grid(grid) {}

    void checkCollision();

    void checkCollisionByType(Object* obj1, Object* obj2);

    void clCircleCircle(Object* obj1, Object* obj2);

    void clCircleRect(Object* obj1, Object* obj2);

    bool aabb(Object* obj1, Object* obj2);

    void clRectRect(Object* obj1, Object* obj2);

    void addClPair(Object* obj1, Vector2 pointA, Object* obj2, Vector2 pointB, float depth);
    void deleteClPair(CollisionPair* pair);

    // returns a pointer to collisionpair vector
    std::vector<CollisionPair*>* getClPairsptr();

private:
    std::vector<CollisionPair*> m_collisionPairs;
    GridPartition* m_grid;
};
