#pragma once
#include "Vector2.h"

struct Object;

struct CollisionPair {
    Object* objectA;
    Vector2 pointA; // deepest point of object A in object B
    Object* objectB;
    Vector2 pointB; // deepest point of object B in object A
    Vector2 normal;
    float depth;
    bool hasCollision;

    CollisionPair(Object* obj1, Vector2 PointA, Object* obj2, Vector2 PointB, float depth, bool hasCol = true)
        : objectA(obj1)
        , pointA(PointA)
        , objectB(obj2)
        , pointB(PointB)
        , depth(depth)
        , hasCollision(hasCol) {
        normal = pointA - pointB;
        normal.normalize(); // calculates a normal vector from objectB to objectA
    }

    ~CollisionPair() = default;
};
