#include "Objects.h"

struct Object;

struct CollisionPair {
    Object* objectA;
    Object* objectB;
    float depth;
    bool hasCollision;
};