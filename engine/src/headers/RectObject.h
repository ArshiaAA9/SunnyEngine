#pragma once

#include "Objects.h"

namespace SE {
struct RectObject : public Object {
    int height;
    int width;

    // constructor:
    // FIX: inertia is being calculated before object, height and with are initialized
    RectObject(float x, float y, float mass, float width, float height, float angle, float cof)
        : Object(x, y, mass, RECT, angle, calculateInertia(mass, width, height), cof)
        , height(height)
        , width(width) {
        checkValidDimensions();
        this->transform.vertices = {
            Vector2(-width / 2, height / 2), Vector2(-width / 2, -height / 2), Vector2(width / 2, -height / 2),
            Vector2(width / 2, height / 2)};
        this->transform.transformedVertices.resize(4);
    }

    RectObject(float x, float y, float width, float height, float angle, float cof)
        // FIX: NOT SURE WHAT TO PASS IN FOR STATIC OBJECTS MASS
        : Object(x, y, RECT, angle, calculateInertia(0, width, height), cof)
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
} // namespace SE
