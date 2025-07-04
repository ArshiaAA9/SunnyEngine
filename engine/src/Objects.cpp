#include "headers/Objects.h"

#include <iostream>

namespace SE {

// Objects Base Functions:
void Object::applyForce(Vector2 force) { this->force += force; }

void Object::setVelocity(Vector2 velocity) { this->velocity = velocity; }

void Object::addVelocity(Vector2 velocity) { this->velocity += velocity; }

// printProperties() virtual function:
void Object::printProperties() const {
    std::cout << "Position: (" << this->transform.position.x << ", " << this->transform.position.y << ")"
              << " Velocity: (" << this->velocity.x << ", " << this->velocity.y << ")"
              << " Force: (" << this->force.x << ", " << this->force.y << ")";
}

void Object::checkValidValues() const {
    if (!isStatic) {
        if (this->mass <= 0.0f) throw std::invalid_argument("Mass must be positive value");
    }
    if (!(0 <= cof && cof <= 1)) {
        std::cerr << "error: coeffisient of restitution should be withing 0 and 1";
    }
}

} // namespace SE
