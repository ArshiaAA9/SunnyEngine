#pragma once

#include <iostream>
#include <ostream>

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

    float mass;
    Vector2 velocity;
    Vector2 force;
    Transform transform;
    ObjectType type;

    // static body related members
    bool isStatic;
    // NOTE: do calculations with inverted mass. Inverted Mass of static objects are 0
    float invertedMass;

    // non-static object constructor
    Object(float x, float y, float mass, ObjectType type, float angle)
        : transform(x, y, *this, angle)
        , mass(mass)
        , type(type)
        , velocity(0, 0)
        , force(0, 0) {
        std::cout << "creating non-static object;" << std::endl;
        checkValidValues();
        invertedMass = 1.0f / mass;
    }

    // static object constructor
    Object(float x, float y, ObjectType type, float angle)
        : transform(x, y, *this, angle)
        , type(type)
        , mass(0)
        , velocity(0, 0)
        , force(0, 0)
        , isStatic(true) {
        std::cout << "creating static object" << std::endl;
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
    RectObject(float x, float y, float mass, float width, float height, float angle)
        : Object(x, y, mass, RECT, angle)
        , height(height)
        , width(width) {
        checkValidDimensions();
        this->transform.vertices = {
            Vector2(-width / 2, height / 2), Vector2(-width / 2, -height / 2),
            Vector2(width / 2, -height / 2), Vector2(width / 2, height / 2)};
        this->transform.transformedVertices.resize(4);
    }

    RectObject(float x, float y, float width, float height, float angle)
        : Object(x, y, RECT, angle)
        , height(height)
        , width(width) {
        checkValidDimensions();
        this->transform.vertices = {
            Vector2(-width / 2, height / 2), Vector2(-width / 2, -height / 2),
            Vector2(width / 2, -height / 2), Vector2(width / 2, height / 2)};
        this->transform.transformedVertices.resize(4);
    }

    ~RectObject() = default;

    Dimensions getDimensions() const override;
    ObjectType getType() const override;

    void printProperties() const override;

private:
    void checkValidDimensions() const;
};

struct CircleObject : public Object {
    float radius;

    // constructor:
    CircleObject(float x, float y, float mass, float radius, float angle)
        : Object(x, y, mass, CIRCLE, angle)
        , radius(radius) {
        checkValidDimensions();
    }

    CircleObject(float x, float y, float radius, float angle)
        : Object(x, y, CIRCLE, angle)
        , radius(radius) {
        checkValidDimensions();
    }

    ~CircleObject() = default;

    /**@return Vector2(radius, Circumference)*/
    Dimensions getDimensions() const override;
    ObjectType getType() const override;

    void printProperties() const override;

private:
    void checkValidDimensions() const;
};

} // namespace SE
