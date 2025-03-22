#pragma once

#include <vector>

#include "Vector2.h"

struct Transform { // Describes an objects location

    Vector2 position;

    Transform(float x, float y)
        : position(x, y) {}

    void moveTo(Vector2 position) { this->position = position; }
};
