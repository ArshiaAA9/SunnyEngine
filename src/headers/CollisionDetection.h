#pragma once

#include <vector>
#include "Objects.h"
#include "GridPartition.h"
#include "CollisionPair.h"


class CollisionDetection {
public:

    void checkCollision(GridPartition grid);

    void clCircleCircle(CircleObject& c1, CircleObject& c2);

    void clCircleRect(CircleObject& c, RectObject& rect);

    bool AABB(RectObject& r1, RectObject& r2);

    void clRectRect(RectObject& r1, RectObject& r2);

private:
    CollisionPair* createCollisions(Object* obj1, Object* obj2);
    std::vector<CollisionPair*> m_collisions;

    CollisionDetection() = default;
    friend class Init;
};

