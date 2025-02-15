#include "Objects.h"

void Object::applyForce(Vector2 force){

    force += force;
    
}

void Object::printProperties() const{

    std::cout << "Position: (" << this->transform.position.x << ", " << this->transform.position.y << ")" 
    << " Velocity: (" << this->velocity.x << ", " << this->velocity.y << ")" 
    << " Force: (" << this->force.x << ", " << this->force.y << ")\n";
}


void Object::checkValidValues(float mass){
    if (mass <= 0.0f){
        throw std::invalid_argument("Mass must be positive value");
    }
}

Vector2 RectObject::getHeightWidth(){
    return Vector2(height, width); 
}

void RectObject::checkValidDimensions(float mass, float height, float width){
    // Helper function to check validity. used in constructors to avoid division by 0,0 Mass and negative friction
    if (mass <= 0 || height <= 0 || width <= 0) {
        throw std::invalid_argument("Mass, height, and width must be positive int.");
    }
}

Vector2 CircleObject::getHeightWidth(){
    return Vector2(radius * 2, radius * 2); 
}


    