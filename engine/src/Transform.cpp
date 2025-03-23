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
    // NOTE: set hasTransformed to false after every kind of movement
    std::cout << " angle1: " << this->cachedAngle << " angle: " << angle << '\n';
    // if object hasnt rotated no need to calculate Sin, Cos and angle
    if (cachedAngle != angle) {
        rotate(angle);
        cachedAngle = angle;
        std::cout << " rotated by :" << angle << '\n';
    }
    calculateRectVertices(); // NOTE: THIS WORKS ONLY FOR RECTS RIGHT NOW
    std::cout << " calculating verices\n";
    transformedVertices.resize(vertices.size());
    float px = position.x;
    float py = position.y;
    for (size_t i = 0; i < vertices.size(); i++) {
        // go over each vertex starting top left counter clockwise
        Vector2 vertex = vertices[i];
        float x = (vertex.x - px) * cosValue - (vertex.y - py) * sinValue + px;
        float y = (vertex.x - px) * sinValue + (vertex.y - py) * cosValue + py;
        transformedVertices[i] = Vector2(x, y);
        std::cout << " side: " << i << " old: " << vertex.x << ',' << vertex.y << " new: " << x << ',' << y;
    }
    std::cout << '\n';
}

// private:

void Transform::rotate(float deltaAngle) {
    angle += deltaAngle;
    sinValue = std::sin(angle);
    cosValue = std::cos(angle);
}

void Transform::calculateRectVertices() {
    Vector2 dimensions = this->ownerObject.getDimensions();
    this->vertices.clear(); // Clear existing vertices
    this->vertices.push_back(Vector2(position.x - dimensions.x / 2, position.y + dimensions.y / 2)); // Top-left
    this->vertices.push_back(Vector2(position.x - dimensions.x / 2, position.y - dimensions.y / 2)); // Bottom-left
    this->vertices.push_back(Vector2(position.x + dimensions.x / 2, position.y - dimensions.y / 2)); // Bottom-right
    this->vertices.push_back(Vector2(position.x + dimensions.x / 2, position.y + dimensions.y / 2)); // Top-right
}
} // namespace SE
