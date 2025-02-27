#pragma once

#include <vector>
#include "Objects.h"
#include "GridPartition.h"
#include "CollisionPair.h"


class CollisionDetection {
public:

    void checkCollision(GridPartition grid);

    void checkCollisionByType(Object* obj1, Object* obj2);

    void clCircleCircle(CircleObject& c1, CircleObject& c2);

    void clCircleRect(CircleObject& c, RectObject& rect);

    bool aabb(RectObject& r1, RectObject& r2);

    void clRectRect(RectObject& r1, RectObject& r2);


private:
    void createCollisionPair(Object* obj1, Object* obj2, float depth);
    std::vector<CollisionPair*> m_collisions;

    CollisionDetection() = default;
    friend class Init;
};

