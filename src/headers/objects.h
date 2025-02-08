#pragma once

#include <iostream>
#include "vector2.h"


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


    //constructor for float x, float y, float mass with no velocity or acceleration where x and y are the center of the obj
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



    // Helper function to check validity. used in constructors to avoid division by 0 and 0 mass
    void checkValidDimensions(float mass, float height, float width) {
        if (mass <= 0 || height <= 0 || width <= 0) {
            throw std::invalid_argument("Mass, height, and width must be positive int.");
        }
    }



    //default constructor uses base Object class default constructor with heigh and width
    rectObject(float x, float y, float mass, float height, float width) 
        : Object(x, y, mass), height(height), width(width)  {
        
            checkValidDimensions(mass, height, width);
        }


    //constructor with all the parameters
    rectObject(float px, float py, float vx, float vy, float  ax, float  ay, float mass, float height, float width)
        : Object(px, py, vx, vy, ax, ay, mass), height(height), width(width) {
            
            checkValidDimensions(mass, height, width);
        }
};