#pragma once

#include "Types.h"
#include "Vector2.h"

namespace SE {
class Object;

struct CollisionPair {
    ObjectPtr objectA;
    Vector2 pointA; // deepest point of object A in object B
    ObjectPtr objectB;
    Vector2 pointB; // deepest point of object B in object A
    float depth;
    Vector2 normal;
    float averageRestitution;
    Vector2 contactPoint = (this->pointA + this->pointB) * 0.5f;
    // change this if there was problem with the direction of resolve
    Vector2 r1 = contactPoint - objectA->transform.position;
    Vector2 r2 = contactPoint - objectB->transform.position;

    CollisionPair(ObjectPtr obj1, Vector2 PointA, ObjectPtr obj2, Vector2 PointB, float depth, Vector2 normal)
        : objectA(obj1)
        , pointA(PointA)
        , objectB(obj2)
        , pointB(PointB)
        , depth(depth)
        , normal(normal) {
        this->averageRestitution = (objectA->getRestitution() + objectB->getRestitution()) / 2;
    }

    ~CollisionPair() = default;
};
} // namespace SE
