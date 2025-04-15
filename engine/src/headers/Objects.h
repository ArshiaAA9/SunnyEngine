#pragma once

#include <algorithm>
#include <iostream>

#include "Transform.h"
#include "Vector2.h"

namespace SE {
enum ObjectType { CIRCLE, RECT };

struct Object {

    float mass;
    Vector2 velocity;
    Vector2 force;

    ObjectType type;
    Transform transform;

    // constructor:
    Object(float x, float y, float mass, ObjectType type, float angle)
        : transform(x, y, *this, angle)
        , mass(mass)
        , type(type)
        , velocity(0, 0)
        , force(0, 0) {
        checkValidValues();
    }

    virtual ~Object() = default;

    virtual Vector2 getDimensions() const = 0;
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
    RectObject(float x, float y, float mass, float height, float width, float angle)
        : Object(x, y, mass, RECT, angle)
        , height(height)
        , width(width) {
        checkValidDimensions();
        this->transform.vertices = {
            Vector2(-width / 2, height / 2), Vector2(-width / 2, -height / 2), Vector2(width / 2, -height / 2),
            Vector2(width / 2, height / 2)};
        this->transform.transformedVertices.resize(4);
    }

    ~RectObject() = default;

    Vector2 getDimensions() const override;
    ObjectType getType() const override;

    void printProperties() const override;

private:
    void checkValidDimensions() const;
};

struct CircleObject : public Object {
    float radius;

    // constructor:
    CircleObject(float x, float y, float mass, float radius, float angle = 0)
        : Object(x, y, mass, CIRCLE, angle)
        , radius(radius) {}

    ~CircleObject() = default;

    /**@return Vector2(radius, Circumference)*/
    Vector2 getDimensions() const override;
    ObjectType getType() const override;

    void printProperties() const override;

private:
    void checkValidDimensions() const;
};
} // namespace SE
