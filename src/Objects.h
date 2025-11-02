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

class Object {
public:
    Transform transform;
    Vector2 velocity = Vector2(0, 0);
    float angularVelocity = 0;

    // these two reset every frame
    Vector2 force = Vector2(0, 0);
    float torque = 0;

protected:
    float m_mass;
    ObjectType m_type;
    bool m_isStatic;
    float m_inertia;
    float m_invertedInertia;
    float m_invertedMass;    // Inverted Mass of static objects are 0
    float m_restitution = 1; // coeffisient of restitution

public:
    // non-static object constructor
    Object(float x, float y, float mass, ObjectType type, float inertia)
        : transform(x, y, *this)
        , m_mass(mass)
        , m_type(type)
        , m_isStatic(false)
        , m_inertia(inertia)
        , m_invertedInertia(1 / inertia) {
        checkValidValues();
        m_invertedMass = 1.0f / mass;
    }

    // static object constructor
    Object(float x, float y, ObjectType type, float inertia)
        : transform(x, y, *this)
        , m_mass(0)
        , m_type(type)
        , m_isStatic(true)
        , m_inertia(inertia)
        , m_invertedInertia(0) {
        checkValidValues();
        m_invertedMass = 0;
    }

    virtual ~Object() = default;

    virtual Dimensions getDimensions() const = 0;

    virtual void printProperties() const;
    void applyForce(Vector2 force);
    void setForce(Vector2 force);
    void applyTorque(float torque);
    void setTorque(float torque);

    void addVelocity(Vector2 veloctiy);
    void setVelocity(Vector2 velocity);

    void addAngularVelocity(float angularVelocity);
    void setAngularVelocity(float angularVelocity);

    // its virtual because we have to calculate inertia differently
    // depending on object type and we have to recalculate it each time
    virtual void setMass(float mass) = 0;

    float getInvertedInertia() const;
    float getInertia() const;
    float getMass() const;
    float getInvertedMass() const;
    ObjectType getType() const;
    float getRestitution() const;

    bool isStatic() const;

private:
    void checkValidValues() const;
};

} // namespace SE
