#include "headers/Objects.h"

namespace SE {

// Objects Base Functions:
void Object::applyForce(Vector2 force) { this->force += force; }

void Object::move(Vector2 amount) {
    this->transform.position += amount;
    this->transform.hasTransformed = false;
}

void Object::setVelocity(Vector2 velocity) { this->velocity = velocity; }

void Object::addVelocity(Vector2 velocity) { this->velocity += velocity; }

// printProperties() virtual function:
void Object::printProperties() const {
    std::cout << "Position: (" << this->transform.position.x << ", " << this->transform.position.y << ")"
              << " Velocity: (" << this->velocity.x << ", " << this->velocity.y << ")"
              << " Force: (" << this->force.x << ", " << this->force.y << ")";
}

void RectObject::printProperties() const {
    std::cout << " topleft: " << this->transform.vertices[0].x << ',' << this->transform.vertices[0].y;
    std::cout << " botleft: " << this->transform.vertices[1].x << ',' << this->transform.vertices[1].y;
    std::cout << " botRight: " << this->transform.vertices[2].x << ',' << this->transform.vertices[2].y;
    std::cout << " topRight: " << this->transform.vertices[3].x << ',' << this->transform.vertices[3].y << '\n';
    // Object::printProperties();
    // std::cout << " Dimensions: " << this->width << "," << this->height << "\n";
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
} // namespace SE
