#include "headers/Objects.h"

// Objects Base Functions:
void Object::applyForce(Vector2 force) { force += force; }

// printProperties() virtual function:
void Object::printProperties() const {
    std::cout << "Position: (" << this->transform.position.x << ", " << this->transform.position.y << ")"
              << " Velocity: (" << this->velocity.x << ", " << this->velocity.y << ")"
              << " Force: (" << this->force.x << ", " << this->force.y << ")\n";
}

void RectObject::printProperties() const {
    std::cout << "Position: (" << this->transform.position.x << ", " << this->transform.position.y << ")"
              << " Velocity: (" << this->velocity.x << ", " << this->velocity.y << ")"
              << " Force: (" << this->force.x << ", " << this->force.y << ")"
              << " Dimensions: " << this->width << "," << this->height << "\n";
}

void CircleObject::printProperties() const {
    std::cout << "Position: (" << this->transform.position.x << ", " << this->transform.position.y << ")"
              << " Velocity: (" << this->velocity.x << ", " << this->velocity.y << ")"
              << " Force: (" << this->force.x << ", " << this->force.y << ")"
              << " Radius: " << this->radius << "\n";
}

void Object::checkValidValues(float mass) const {
    if (mass <= 0.0f) {
        throw std::invalid_argument("Mass must be positive value");
    }
}

void RectObject::checkValidDimensions(float mass, float height, float width) const {
    // Helper function to check validity. used in constructors to avoid division
    // by 0,0 Mass and negative friction
    if (mass <= 0 || height <= 0 || width <= 0) {
        throw std::invalid_argument("Mass, height, and width must be positive int.");
    }
}

/**@return Vector2(height, width)*/
Vector2 RectObject::getDimensions() const { return Vector2(height, width); }

/**@return Vector2(radius, Circumference)*/
Vector2 CircleObject::getDimensions() const { return Vector2(radius, radius * 2); }
