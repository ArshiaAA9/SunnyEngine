#pragma once

#include <iostream>
#include <vector>
#include "Vector2.h"
#include "Physics.h"
#include "Colliders.h"
#include "Transform.h"
#include "GridPartition.h"

struct Object;
struct RectObject;
struct CircleObject;

//physical objects
struct Object {
    

    float mass;
    Vector2 velocity; 
    Vector2 force;

    Transform transform; // position and scale
    Collider collider; 


    Object(float x, float y, float mass)
        : transform(x, y)
        , mass(mass){

            checkValidValues(mass); // validate values
        }

    ~Object() = default;


    void applyForce(Vector2 force);

    // void updateVelocityAfterImpact(Object& cO){
    //     //1 obj Velocity 2 collided object cO = collidedObject
    //     Vector2 dV = Velocity - cO.Velocity;
    //     Vector2 dPos = Position - cO.Position;
    //     float massSum = Mass + cO.Mass;
    //     float dotDVdPos = dotProduct(dV, dPos);
    //     float distanceSquared = squaredLengthOf2Pos(Position, cO.Position);
    //     float scale = (2.0f / massSum) * (dotDVdPos / distanceSquared);
    //     Velocity = Velocity - (scale * cO.Mass) * dPos;         // Uses dPos
    //     cO.Velocity = cO.Velocity + (scale * Mass) * dPos;    
    // }



    void printProperties() const;

    virtual void getHeightWidth() = 0;

private:

    void checkValidValues(float mass);

};


struct RectObject : public Object {
    
    int height;
    int width;


    RectObject(float x, float y, float mass, float height, float width)
        : Object(x, y, mass)
        , height(height)
        , width(width){

            checkValidDimensions(mass, height, width);
        }
    ~RectObject() = default;

    void getHeightWidth();
private:
    // void checkCollisionRectwithRect(RectObject& collidedRect){
    //     float halfWidth1 = width / 2, halfHeight1 = height / 2;
    //     float halfWidth2 = collidedRect.width / 2, halfHeight2 = collidedRect.height / 2;
    //     float r1LeftX = Position.x - halfWidth1;
    //     float r1RightX = Position.x + halfWidth1;
    //     float r1TopY = Position.y - halfHeight1;
    //     float r1BottomY = Position.y + halfHeight1;
    //     float r2LeftX = collidedRect.Position.x - halfWidth2;
    //     float r2RightX = collidedRect.Position.x + halfWidth2;
    //     float r2TopY = collidedRect.Position.y - halfHeight2;
    //     float r2BottomY = collidedRect.Position.y + halfHeight2;
    //     if((r1LeftX < r2RightX) && (r1RightX > r2LeftX)&&
    //        (r1BottomY < r2TopY) && (r1TopY > r2BottomY)){
    //         updateVelocityAfterImpact(collidedRect);
    //     }
    // }
 

    void checkValidDimensions(float mass, float height, float width);
};



struct CircleObject : public Object{
    
    float radius;


    CircleObject(float x, float y, float mass, float radius) 
        : Object(x, y, mass)
        , radius(radius) {
    }
    ~CircleObject() = default;

    void getHeightWidth();
    
private:


};