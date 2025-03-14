#include "headers/Objects.h"

// Objects Base Functions:
void Object::applyForce(Vector2 force) { this->force += force; }

// printProperties() virtual function:
void Object::printProperties() const {
    std::cout << "Position: (" << this->transform.position.x << ", " << this->transform.position.y << ")"
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
    // Helper function to check validity. used in constructors to avoid division
    // by 0,0 Mass and negative friction
    if (this->height <= 0 || this->width <= 0) {
        throw std::invalid_argument("Height, and width must be positive int.");
    }
}

void CircleObject::checkValidDimensions() const {
    // Helper function to check validity. used in constructors to avoid division
    // by 0,0 Mass and negative friction
    if (this->radius <= 0) {
        throw std::invalid_argument("Radius must be positive int.");
    }
}

// getType pure virtual function:
ObjectType RectObject::getType() const { return this->type; }

ObjectType CircleObject::getType() const { return this->type; }

// getDimensions pure virtual function:
/**@return Vector2(height, width)*/
Vector2 RectObject::getDimensions() const { return Vector2(height, width); }

/**@return Vector2(radius, diameter)*/
Vector2 CircleObject::getDimensions() const { return Vector2(radius, radius * 2); }
