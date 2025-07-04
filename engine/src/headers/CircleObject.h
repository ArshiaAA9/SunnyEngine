#pragma once
#include "Objects.h"

namespace SE {

struct CircleObject : public Object {
    float radius;

    // constructor:
    CircleObject(float x, float y, float mass, float radius, float angle, float cof)
        : Object(x, y, mass, CIRCLE, angle, calculateInertia(mass, radius), cof)
        , radius(radius) {
        checkValidDimensions();
    }

    CircleObject(float x, float y, float radius, float angle, float cof)
        // FIX: NOT SURE WHAT TO PASS IN FOR STATIC OBJECTS MASS
        : Object(x, y, CIRCLE, angle, calculateInertia(0, radius), cof)
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
