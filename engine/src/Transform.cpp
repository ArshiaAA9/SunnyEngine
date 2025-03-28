#include "headers/Transform.h"

#include <iostream>

#include "headers/Objects.h"

namespace SE {

// publics:

void Transform::moveTo(Vector2 position) {
    this->position = position;
    hasTransformed = false;
}

void Transform::transform() {
    // go over vertices and transform them
    if (hasTransformed == false) {
        for (size_t i = 0; i < transformedVertices.size(); i++) {
            transformedVertices[i] = rotate(vertices[i]);
        }
        hasTransformed = true;
    }
}

// private:

Vector2 Transform::rotate(Vector2 vector) {
    // x1 = x0cos(θ) – y0sin(θ)(Equation 1)
    // y1 = x0sin(θ) + y0cos(θ)(Equation 2)

    float rx = vector.x * this->cosValue - vector.y * this->sinValue;
    float ry = vector.x * this->sinValue + vector.y * this->cosValue;

    float tx = rx + position.x;
    float ty = ry + position.y;

    return Vector2(tx, ty);
}

} // namespace SE
