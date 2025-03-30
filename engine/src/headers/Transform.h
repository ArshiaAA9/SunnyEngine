#pragma once

#include <vector>

#include "Vector2.h"

namespace SE {
class Object;

struct Transform {
public:
    Vector2 position;
    bool hasTransformed;
    std::vector<Vector2> vertices;
    std::vector<Vector2> transformedVertices;
    float angle = 0;
    float sinValue;
    float cosValue;

    // constructor:
    Transform(float x, float y, Object& object, float angle)
        : position(x, y)
        , ownerObject(object) {
        sinValue = std::sin(angle);
        cosValue = std::cos(angle);
    }

    void moveTo(Vector2 position);

    void transform();
    void changeAngle(float amount);

private:
    void calculateRectVertices();
    void rotate(float amount);
    Vector2 rotate(Vector2 vector);

    Object& ownerObject;
    float cachedAngle = 0;
};
} // namespace SE
