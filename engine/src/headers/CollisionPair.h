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

    CollisionPair(ObjectPtr obj1, Vector2 PointA, ObjectPtr obj2, Vector2 PointB, float depth, Vector2 normal)
        : objectA(obj1)
        , pointA(PointA)
        , objectB(obj2)
        , pointB(PointB)
        , depth(depth)
        , normal(normal) {}

    ~CollisionPair() = default;
};
} // namespace SE
