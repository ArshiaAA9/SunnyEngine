#pragma once

#include <vector>

#include "Vector2.h"

namespace SE {
struct Object;

struct Transform {
public:
    Vector2 position;
    std::vector<Vector2> vertices;
    std::vector<Vector2> transformedVertices;
    float angle;
    float sinValue;
    float cosValue;

    // constructor:
    Transform(float x, float y, Object& object, float angle)
        : position(x, y)
        , ownerObject(object) {
        changeAngle(angle);
    }

    void move(Vector2 amount);
    void moveTo(Vector2 position);

    void transform();
    void increaseAngle(float amount);
    void changeAngle(float amount);

    void printVertices() const;

private:
    void calculateRectVertices();
    Vector2 rotate(Vector2 vector);

    Object& ownerObject;
    bool hasTransformed;
};
} // namespace SE
