#pragma once

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

    // static body related members
    bool isStatic;
    // Inverted Mass of static objects are 0
    float invertedMass;

    float inertia;
    float invertedInertia;

    // non-static object constructor
    Object(float x, float y, float mass, ObjectType type, float angle, float inertia)
        : transform(x, y, *this, angle)
        , mass(mass)
        , type(type)
        , velocity(0, 0)
        , force(0, 0)
        , isStatic(false)
        , inertia(inertia)
        , invertedInertia(1 / inertia) {
        checkValidValues();
        invertedMass = 1.0f / mass;
    }

    // static object constructor
    Object(float x, float y, ObjectType type, float angle, float inertia)
        : transform(x, y, *this, angle)
        , mass(0)
        , type(type)
        , velocity(0, 0)
        , force(0, 0)
        , isStatic(true)
        , inertia(inertia)
        , invertedInertia(1 / inertia) {
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

struct RectObject : public Object {
    int height;
    int width;

    // constructor:
    // FIX: inertia is being calculated before object, height and with are initialized
    RectObject(float x, float y, float mass, float width, float height, float angle)
        : Object(x, y, mass, RECT, angle, calculateInertia(mass, width, height))
        , height(height)
        , width(width) {
        checkValidDimensions();
        this->transform.vertices = {
            Vector2(-width / 2, height / 2), Vector2(-width / 2, -height / 2), Vector2(width / 2, -height / 2),
            Vector2(width / 2, height / 2)};
        this->transform.transformedVertices.resize(4);
    }

    RectObject(float x, float y, float width, float height, float angle)
        // FIX: NOT SURE WHAT TO PASS IN FOR STATIC OBJECTS MASS
        : Object(x, y, RECT, angle, calculateInertia(0, width, height))
        , height(height)
        , width(width) {
        checkValidDimensions();
        this->transform.vertices = {
            Vector2(-width / 2, height / 2), Vector2(-width / 2, -height / 2), Vector2(width / 2, -height / 2),
            Vector2(width / 2, height / 2)};
        this->transform.transformedVertices.resize(4);
    }

    ~RectObject() = default;

    Dimensions getDimensions() const override;
    ObjectType getType() const override;

    void printProperties() const override;

private:
    void checkValidDimensions() const;
    float calculateInertia(float mass, float width, float height);
};

struct CircleObject : public Object {
    float radius;

    // constructor:
    CircleObject(float x, float y, float mass, float radius, float angle)
        : Object(x, y, mass, CIRCLE, angle, calculateInertia(mass, radius))
        , radius(radius) {
        checkValidDimensions();
    }

    CircleObject(float x, float y, float radius, float angle)
        // FIX: NOT SURE WHAT TO PASS IN FOR STATIC OBJECTS MASS
        : Object(x, y, CIRCLE, angle, calculateInertia(0, radius))
        , radius(radius) {
        checkValidDimensions();
    }

    ~CircleObject() = default;

    /**@return Vector2(radius, Circumference)*/
    Dimensions getDimensions() const override;
    ObjectType getType() const override;

    void printProperties() const override;

private:
    float calculateInertia(float mass, float radius);
    void checkValidDimensions() const;
};

} // namespace SE
