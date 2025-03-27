#include "headers/Transform.h"

#include "headers/Objects.h"

namespace SE {
// constructor:
Transform::Transform(float x, float y, Object& object, float angle)
    : position(x, y)
    , ownerObject(object) {
    if (ownerObject.getType() == RECT) {
        vertices.reserve(4);
        transformedVertices.resize(4);
        float width = this->ownerObject.getDimensions().x;
        float height = this->ownerObject.getDimensions().y;

        this->vertices.push_back(Vector2(-width / 2, position.y + height / 2)); // Top-left
        this->vertices.push_back(Vector2(-width / 2, position.y - height / 2)); // Bottom-left
        this->vertices.push_back(Vector2(width / 2, position.y - height / 2));  // Bottom-right
        this->vertices.push_back(Vector2(width / 2, position.y + height / 2));  // Top-right
    }
}

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
    float ry = vector.y * this->sinValue + vector.y * this->cosValue;

    float tx = rx + position.x;
    float ty = ry + position.y;

    return Vector2(tx, ty);
}

void Transform::rotate(float deltaAngle) {
    angle += deltaAngle;
    sinValue = std::sin(angle);
    cosValue = std::cos(angle);
}

} // namespace SE
