#pragma once
#include <iostream>

#include "Types.h"
#include "Vector2.h"

namespace SE {
struct Object;

struct CollisionPair {
    ObjectPtr objectA;
    Vector2 pointA; // deepest point of object A in object B
    ObjectPtr objectB;
    Vector2 pointB; // deepest point of object B in object A
    Vector2 normal;
    float depth;
    bool hasCollision;

    CollisionPair(ObjectPtr obj1, Vector2 PointA, ObjectPtr obj2, Vector2 PointB, float depth, bool hasCol = true)
        : objectA(obj1)
        , pointA(PointA)
        , objectB(obj2)
        , pointB(PointB)
        , depth(depth)
        , hasCollision(hasCol) {
        normal = objectA->transform.position - objectB->transform.position;
        normal.normalize(); // gives a direction from B to A where Object A is the one that has to be moved
        // std::cout << " normal: " << normal.x << ',' << normal.y << " pointA:" << pointA.x << ','
        //          << pointA.y << " pointB " << pointB.x << ',' << pointB.y << " depth: " << depth
        //          << '\n';
    }

    ~CollisionPair() = default;
};
} // namespace SE
