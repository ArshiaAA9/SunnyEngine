#include "Objects.h"

struct Object;

struct CollisionPair {
    Object* objectA;
    Object* objectB;
    float depth;
    bool hasCollision;

    CollisionPair(Object* obj1, Object* obj2, float depth, bool hasCol = true) 
    : objectA(obj1)
    , objectB(obj2)
    , depth(depth)
    , hasCollision(hasCol) {}
};