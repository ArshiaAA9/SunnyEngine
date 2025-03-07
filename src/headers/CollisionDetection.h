#pragma once

#include <vector>

#include "CollisionPair.h"
#include "GridPartition.h"
#include "Objects.h"

class GridPartition;
class PhysicsWorld;

class CollisionDetection {
public:
    CollisionDetection(GridPartition* grid) : m_grid(grid) {}

    void checkCollision();

    void checkCollisionByType(Object* obj1, Object* obj2);

    void clCircleCircle(CircleObject& c1, CircleObject& c2);

    void clCircleRect(CircleObject& c, RectObject& rect);

    bool aabb(RectObject& r1, RectObject& r2);

    void clRectRect(RectObject& r1, RectObject& r2);

    void addClPair(Object* obj1, Vector2 pointA, Object* obj2, Vector2 pointB, float depth);
    void deleteClPair(CollisionPair* pair);

    // returns a pointer to collisionpair vector
    std::vector<CollisionPair*>* getClPairsptr();

private:
    std::vector<CollisionPair*> m_collisionPairs;
    GridPartition* m_grid;
};
