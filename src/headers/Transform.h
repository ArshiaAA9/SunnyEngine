#pragma once

#include "Vector2.h"

struct Transform { // Describes an objects location

    Vector2 position;
    float Scale = 1;

    Transform(float x, float y) : position(x, y) {}

};