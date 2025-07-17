#pragma once
#include "Objects.h"

namespace SE {

struct CircleObject : public Object {
    float radius;

    // constructor:
    CircleObject(float x, float y, float mass, float radius)
        : Object(x, y, mass, CIRCLE, calculateInertia(mass, radius))
        , radius(radius) {
        checkValidDimensions();
    }

    CircleObject(float x, float y, float radius)
        : Object(x, y, CIRCLE, calculateInertia(0, radius))
        , radius(radius) {
        checkValidDimensions();
    }

    ~CircleObject() = default;

    Dimensions getDimensions() const override;
    ObjectType getType() const;

    void printProperties() const override;
    void setMass(float mass) override;

private:
    static float calculateInertia(float mass, float radius);
    void checkValidDimensions() const;
};
} // namespace SE
