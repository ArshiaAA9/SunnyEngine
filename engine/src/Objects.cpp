#include "headers/Objects.h"

namespace SE {

// Objects Base Functions:
void Object::applyForce(Vector2 force) { this->force += force; }

void Object::setVelocity(Vector2 velocity) { this->velocity = velocity; }

void Object::addVelocity(Vector2 velocity) { this->velocity += velocity; }

// printProperties() virtual function:
void Object::printProperties() const {
    std::cout << "Position: (" << this->transform.position.x << ", " << this->transform.position.y
              << ")"
              << " Velocity: (" << this->velocity.x << ", " << this->velocity.y << ")"
              << " Force: (" << this->force.x << ", " << this->force.y << ")";
}

void RectObject::printProperties() const {
    Object::printProperties();
    std::cout << " Dimensions: " << this->width << "," << this->height << "\n";
}

void CircleObject::printProperties() const {
    Object::printProperties();
    std::cout << " Radius: " << this->radius << "\n";
}

void Object::checkValidValues() const {
    if (this->mass <= 0.0f) {
        throw std::invalid_argument("Mass must be positive value");
    }
}

void RectObject::checkValidDimensions() const {
    if (this->height <= 0 || this->width <= 0) {
        throw std::invalid_argument("Height, and width must be positive int.");
    }
}

void CircleObject::checkValidDimensions() const {
    if (this->radius <= 0) {
        throw std::invalid_argument("Radius must be positive int.");
    }
}

// getType pure virtual function:
ObjectType RectObject::getType() const { return this->type; }

ObjectType CircleObject::getType() const { return this->type; }

// getDimensions pure virtual function:
/**@return Dimensions(width, height)*/
Dimensions RectObject::getDimensions() const { return Dimensions(width, height); }

/**@return Dimensions(radius, diameter)*/
Dimensions CircleObject::getDimensions() const { return Dimensions(radius); }
} // namespace SE
