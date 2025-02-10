#pragma once

#include <iostream>
#include "vector2.h"

struct Object;
struct rectObject;
struct CircleObject;


//physical objects
struct Object {

    float mass;
    float frictionK;

    Vector2 position;         // Position of the object
    Vector2 velocity;         // Velocity of the object
    Vector2 acceleration;     // Acceleration of the object



    /**
     * constructs an Object with given position, mass, friction, velocity, and acceleration.
     * 
     * @param px X-coordinate of the object (cant be empty)
     * @param py Y-coordinate of the object (cant be empty)
     * @param mass mass of the object (1 by default, cant be negative)
     * @param vx velocity of the object in x axis (0 by default)
     * @param vy velocity of the object in y axis (0 by default)
     * @param ax acceleration of the object in x axis (0 by default)
     * @param ay acceleration of the object in y axis (0 by default)
     * @param frictionK friction coefficient of the object no friction from this object if 0 (0 by default)
     */
    Object(float px, float py, float mass = 1.0f, float vx = 0.0f, float vy = 0.0f, float ax = 0.0f, float  ay = 0.0f, float frictionK = 0.0f)        
        : position(px, py)
        , mass(mass)
        , velocity(vx, vy)
        , acceleration(ax, ay)
        , frictionK(frictionK) {
            
            checkValidValues(mass, frictionK); // validate values
        
        }



    //1 obj velocity 2 collided object cO = collidedObject
    void updateVelocityAfterImpact(Object& cO){

        Vector2 dV = velocity - cO.velocity;
        Vector2 dPos = position - cO.position;
        float massSum = mass + cO.mass;
        float dotDVdPos = dotProduct(dV, dPos);
        float distanceSquared = squaredLengthOf2Pos(position, cO.position);


        float scale = (2.0f / massSum) * (dotDVdPos / distanceSquared);

        velocity = velocity - (scale * cO.mass) * dPos;         // Uses dPos
        cO.velocity = cO.velocity + (scale * mass) * dPos;    
    }


    // virtual function for detecting collision overriden by all derived classes 
    virtual void detectCollisionAndUpdateVelocity(Object& collidedObj) = 0;


    //find squared length of 2 position
    float squaredLengthOf2Pos(Vector2 pos1, Vector2 pos2){
        float dx = pos1.x - pos2.x;
        float dy = pos1.y - pos2.y;
        return dx * dx + dy * dy;
    }


    //prints position, velocity and acceleration of a object
    void printProperties() const{

        std::cout << "Position: (" << this->position.x << ", " << this->position.y << ")" 
        << " velocity: (" << this->velocity.x << ", " << this->velocity.y << ")" 
        << " acceleration: (" << this->acceleration.x << ", " << this->acceleration.y << ")\n";
    } 

private:

    //used to validate mass or friction.
    void checkValidValues(float mass, float frictionK){
        if (mass <= 0.0f){
            throw std::invalid_argument("Mass must be positive value");

        }else if(frictionK < 0){
            throw std::invalid_argument("Friction Coefficient cannot be negative");
        
        }
        
    }


    //idk how it works
    static float dotProduct(Vector2 vec1, Vector2 vec2){
        return (vec1.x * vec2.x) + (vec1.y * vec2.y);
    }

};



//struct for recangle objects derived from Objects struct
struct rectObject : public Object {
    
    int height;
    int width;



    /**
     * constructs an rectObject with given position, mass, friction, velocity, acceleration and height with width
     * position(x,y) is the center of the rect
     * 
     * @param px X-coordinate of the object (cant be empty)
     * @param py Y-coordinate of the object (cant be empty)
     * @param mass mass of the object (1 by default, cant be negative)
     * @param vx velocity of the object in x axis (0 by default)
     * @param vy velocity of the object in y axis (0 by default)
     * @param ax acceleration of the object in x axis (0 by default)
     * @param ay acceleration of the object in y axis (0 by default)
     * @param frictionK friction coefficient of the object no friction from this object if 0 (0 by default)
     * @param height height of the rect
     * @param width width of the rect 
     */
    rectObject(float px, float py, float mass, float vx, float vy, float  ax, float  ay,float frictionK ,float height, float width)
        : Object(px, py, mass, vx, vy, ax, ay, frictionK), height(height), width(width) {
            
            checkValidDimensions(mass, height, width, frictionK);
        }


    //check the type to see what kind of collision is it
    void detectCollisionAndUpdateVelocity(Object& collidedObj) override{

        std::cout << "something";
        if (rectObject* rect = dynamic_cast<rectObject*>(&collidedObj)) {
            checkCollisionRectwithRect(*rect);  
        } 
        // Try to cast to CircleObject
        else if (CircleObject* circle = dynamic_cast<CircleObject*>(&collidedObj)) {
            checkCollisionRectWithCircle(*circle);
        } 
    }


private:
    //TODO
    void checkCollisionRectWithCircle(CircleObject& collidedCircle){


    }

    void checkCollisionRectwithRect(rectObject& collidedRect){
        float halfWidth1 = width / 2, halfHeight1 = height / 2;
        float halfWidth2 = collidedRect.width / 2, halfHeight2 = collidedRect.height / 2;

        float r1LeftX = position.x - halfWidth1;
        float r1RightX = position.x + halfWidth1;
        float r1TopY = position.y - halfHeight1;
        float r1BottomY = position.y + halfHeight1;

        float r2LeftX = collidedRect.position.x - halfWidth2;
        float r2RightX = collidedRect.position.x + halfWidth2;
        float r2TopY = collidedRect.position.y - halfHeight2;
        float r2BottomY = collidedRect.position.y + halfHeight2;
        
        if((r1LeftX < r2RightX) && (r1RightX > r2LeftX)&&
           (r1BottomY < r2TopY) && (r1TopY > r2BottomY)){
            updateVelocityAfterImpact(collidedRect);
        }
    }
 

    // Helper function to check validity. used in constructors to avoid division by 0,0 mass and negative friction
    void checkValidDimensions(float mass, float height, float width, float frictionK) {
        if (mass <= 0 || height <= 0 || width <= 0 || frictionK < 0) {
            throw std::invalid_argument("Mass, friction ,height, and width must be positive int.");
        }
    }
};


struct triangleObject : public Object {




};


struct CircleObject : public Object{
    
    float radius;

    /**
     * constructs an rectObject with given position, mass, friction, velocity, acceleration and height with width
     * position(x,y) is the center of the rect
     * 
     * @param px X-coordinate of the object (cant be empty)
     * @param py Y-coordinate of the object (cant be empty)
     * @param mass mass of the object (1 by default, cant be negative)
     * @param vx velocity of the object in x axis (0 by default)
     * @param vy velocity of the object in y axis (0 by default)
     * @param ax acceleration of the object in x axis (0 by default)
     * @param ay acceleration of the object in y axis (0 by default)
     * @param frictionK friction coefficient of the object no friction from this object if 0 (0 by default)
     * @param radius radius of the circle
     */
    CircleObject(float px, float py, float mass, float vx, float vy, float ax, float ay, float frictionK, float radius)
        : Object(px, py,mass, vx, vy, ax, ay, frictionK), radius(radius) {}

    
    //check the type to see what kind of collision is it
    void detectCollisionAndUpdateVelocity(Object& collidedObj) override{

        if (CircleObject* circle = dynamic_cast<CircleObject*>(&collidedObj)) {
        
            checkCollisionCircleWithCircle(*circle);
        }
        // Try to cast to CircleObject
        else if(rectObject* rect = dynamic_cast<rectObject*>(&collidedObj)) {
            checkCollisionCirclewithRect(*rect);  
        } 
    }


private:

    void checkCollisionCircleWithCircle(CircleObject& circle){

        //x1 = circle that method is used on x2 = the argument circle
        // distance = sqrt((x2-x1)^2 + (y2-y1)^2)
        float squaredCirclesCenterDistance = squaredLengthOf2Pos(circle.position, position);
        
        //there is collision if the sum of radiuses are bigger than the center distance
        if(squaredCirclesCenterDistance <= (circle.radius + radius) * (circle.radius + radius)){
            
        }
    }

    // If the circle is to the RIGHT of the square, check against the RIGHT edge.
    // If the circle is to the LEFT of the square, check against the LEFT edge.
    // If the circle is ABOVE the square, check against the TOP edge.
    // If the circle is to the BELOW the square, check against the BOTTOM edge.
    void checkCollisionCirclewithRect(rectObject& rect){



    }
};