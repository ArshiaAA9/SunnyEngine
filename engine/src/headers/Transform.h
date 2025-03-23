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

    Transform(float x, float y, Object& object)
        : position(x, y)
        , ownerObject(object) {}

    void moveTo(Vector2 position);

    void transform();

private:
    void calculateRectVertices();
    void rotate(float amount);

    Object& ownerObject;
    float cachedAngle = 0;
};
} // namespace SE
