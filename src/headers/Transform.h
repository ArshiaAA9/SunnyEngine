#pragma once

#include "Vector2.h"
#include "Objects.h"

struct CollisionPoints {
    Vector2 A; // Furthest point of A into B
    Vector2 B; // Furthest point of B into A
    Vector2 Normal; // B - A Normalized
    float Depth; // Length of B - A
    bool HasCollision;
};


struct Transform { // Describes an objects location

    Vector2 position;
    float Scale = 1;

    Transform(float x, float y) : position(x, y) {}

};