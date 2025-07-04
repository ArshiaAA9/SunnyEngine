#pragma once

#include <iostream>

#include "Transform.h"
#include "Vector2.h"

namespace SE {
struct Dimensions {
    float w;
    float h;
    float r;

    Dimensions(float width, float height)
        : w(width)
        , h(height) {}

    Dimensions(float radius)
        : r(radius) {}
};

enum ObjectType { CIRCLE, RECT };

struct Object {

    Transform transform;
    float mass;
    ObjectType type;
    Vector2 velocity;
    Vector2 force;

    bool isStatic;
    float invertedMass; // Inverted Mass of static objects are 0

    float inertia;
    float invertedInertia;
    float cof; // coeffisient of restitution

    // non-static object constructor
    Object(float x, float y, float mass, ObjectType type, float angle, float inertia, float cof)
        : transform(x, y, *this, angle)
        , mass(mass)
        , type(type)
        , velocity(0, 0)
        , force(0, 0)
        , isStatic(false)
        , inertia(inertia)
        , invertedInertia(1 / inertia)
        , cof(cof) {
        checkValidValues();
        invertedMass = 1.0f / mass;
    }

    // static object constructor
    Object(float x, float y, ObjectType type, float angle, float inertia, float cof)
        : transform(x, y, *this, angle)
        , mass(0)
        , type(type)
        , velocity(0, 0)
        , force(0, 0)
        , isStatic(true)
        , inertia(inertia)
        , invertedInertia(1 / inertia)
        , cof(cof) {
        checkValidValues();
        invertedMass = 0;
    }

    virtual ~Object() = default;

    virtual Dimensions getDimensions() const = 0;
    virtual ObjectType getType() const = 0;

    virtual void printProperties() const;

    // dynamics:
    void applyForce(Vector2 force);
    void setVelocity(Vector2 velocity);
    void addVelocity(Vector2 veloctiy);

private:
    void checkValidValues() const;
};

} // namespace SE
