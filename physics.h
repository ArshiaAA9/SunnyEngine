#pragma once

#include <iostream>

const float GRAVITY = 9.81;


// Struct for a 2D vector (for position, velocity, or acceleration)
struct Vector2 {

    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}



    // Addition operator for Vector2
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // Subtraction operator for Vector2
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // Multiplication by a scalar
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // Division by a scalar
    Vector2 operator/(float scalar) const {
        if(scalar == 0){
            throw std::invalid_argument("scalar must be non-zero.");
        }
        return Vector2(x / scalar, y / scalar);
    }
};


//physical objects
struct Object {

    float mass;

    Vector2 position;         // Position of the object
    Vector2 velocity;         // Velocity of the object
    Vector2 acceleration;     // Acceleration of the object



    void checkValidMass(float mass){
        if (mass <= 0){
            throw std::invalid_argument("Mass must be positive int.");
        }
        
    }


    //constructors 
    Object() : position(0, 0), velocity(0, 0), acceleration(0, 0), mass(1) {}


    //constructor for float x, float y, float mass with no velocity or acceleration 
    Object(float x, float y, float mass) 
        : position(x, y), velocity(0, 0), acceleration(0, 0), mass(mass) {}


    //constructor with every parameter
    Object(float px, float py, float vx, float vy, float  ax, float  ay, float mass)        
        : position(px, py), velocity(vx, vy), acceleration(ax, ay), mass(mass) {}



    //prints position , velocity and acceleration of a object
    void printProperties() const{

        std::cout << "Position: (" << this->position.x << ", " << this->position.y << ")" 
        << " velocity: (" << this->velocity.x << ", " << this->velocity.y << ")" 
        << " acceleration: (" << this->acceleration.x << ", " << this->acceleration.y << ")\n";
    } 
};


//struct for recangle objects derived from Objects struct
struct rectObject : public Object {
    
    int height;
    int width;



    // Helper function to check validity used in constructors to avoid division by 0 and 0 mass
    void checkValidDimensions(float mass, float height, float width) {
        if (mass <= 0 || height <= 0 || width <= 0) {
            throw std::invalid_argument("Mass, height, and width must be positive int.");
        }
    }



    //default constructor uses base Object class default constructor with heigh and width
    rectObject(float x, float y, float mass, float height, float width) 
        : Object(x, y, mass), height(height), width(width)  {
        
            checkValidDimensions(mass, height, width);
                    
            // positions are divided by with and height to find weight center of the rect 
            position.x -= position.x / width;
            position.y -= position.y / height;
    }


    //constructor with all the parameters
    rectObject(float px, float py, float vx, float vy, float  ax, float  ay, float mass, float height, float width)
        : Object(px, py, vx, vy, ax, ay, mass), height(height), width(width) {
        
            // positions are divided by with and height to find weight center of the rect 
            position.x -= position.x / width;
            position.y -= position.y / height;
        }
};



void updateObject(Object& obj, float deltaTime) {

    // Update position: new position = initial position+(velocity×Δt)+1/2​×acceleration×(Δt)^2
    obj.position = obj.position + (obj.velocity * deltaTime) + obj.acceleration * (deltaTime * deltaTime )/ 2;

    // Update velocity: v = v + a * dt
    obj.velocity = obj.velocity + obj.acceleration * deltaTime;

}



//uses a = f/m to change the acceleration of an object
void applyForce(Object& obj, Vector2 force){

    obj.acceleration = force/obj.mass;

} 



void applyGravity(Object& obj) {
    obj.acceleration.y -= GRAVITY; // Apply gravity to the y-component of acceleration
}




