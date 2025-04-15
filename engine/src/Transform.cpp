#include "headers/Transform.h"

namespace SE {

// publics:

void Transform::move(Vector2 amount) {
    this->position += amount;
    this->hasTransformed = false;
}

void Transform::moveTo(Vector2 position) {
    this->position = position;
    hasTransformed = false;
}

void Transform::transform() {
    // go over vertices and transform them
    if (hasTransformed == false) {
        for (size_t i = 0; i < transformedVertices.size(); i++) {
            transformedVertices[i] = rotate(vertices[i]) + position;
        }
        hasTransformed = true;
    }
}

void Transform::increaseAngle(float amount) {
    this->angle += amount;
    this->sinValue = std::sin(this->angle);
    this->cosValue = std::cos(this->angle);
    this->hasTransformed = false;
}

void Transform::changeAngle(float amount) {
    this->angle = amount;
    this->sinValue = std::sin(this->angle);
    this->cosValue = std::cos(this->angle);
    this->hasTransformed = false;
}

void Transform::printVertices() const {
    std::cout << "1.vertices: " << this->transformedVertices[0] << '\n'
              << "2.vertices: " << this->transformedVertices[1] << '\n'
              << "3.vertices: " << this->transformedVertices[2] << '\n'
              << "4.vertices: " << this->transformedVertices[3] << std::endl;
}

// private:

Vector2 Transform::rotate(Vector2 vector) {
    // x1 = x0cos(θ) – y0sin(θ)(Equation 1)
    // y1 = x0sin(θ) + y0cos(θ)(Equation 2)

    float rx = vector.x * this->cosValue - vector.y * this->sinValue;
    float ry = vector.x * this->sinValue + vector.y * this->cosValue;

    return Vector2(rx, ry);
}

} // namespace SE
