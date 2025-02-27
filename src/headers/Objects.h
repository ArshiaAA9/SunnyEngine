#pragma once

#include <iostream>
#include <vector>
#include "Vector2.h"
#include "Physics.h"
#include "Transform.h"
#include "GridPartition.h"

struct Object;
struct RectObject;
struct CircleObject;


struct Object {
    enum ObjectType { CIRCLE, RECT };
    
    float mass;
    Vector2 velocity; 
    Vector2 force;

    ObjectType type;
    Transform transform; // position and scale

    Object(float x, float y, float mass, ObjectType type)
        : transform(x, y)
        , mass(mass)
        , type(type){ checkValidValues(mass); }

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

    virtual Vector2 getDimensions() = 0;

private:

    void checkValidValues(float mass);

};


struct RectObject : public Object {
    
    int height;
    int width;


    RectObject(float x, float y, float mass, float height, float width)
        : Object(x, y, mass, RECT)
        , height(height)
        , width(width){
            checkValidDimensions(mass, height, width);
        }
    ~RectObject() = default;

    Vector2 getDimensions() override;
private:

    void checkValidDimensions(float mass, float height, float width);
};



struct CircleObject : public Object{
    
    float radius;


    CircleObject(float x, float y, float mass, float radius) 
        : Object(x, y, mass, CIRCLE)
        , radius(radius) {}
    ~CircleObject() = default;

    Vector2 getDimensions() override;
    
private:


};