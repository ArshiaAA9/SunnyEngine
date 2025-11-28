#pragma once

#include <vector>

#include "Vector2.h"

namespace SE {
class Object;

struct Transform {
public:
    Vector2 position;
    std::vector<Vector2> vertices;
    std::vector<Vector2> transformedVertices;

    // constructor:
    Transform(float x, float y, Object& object)
        : position(x, y)
        , m_ownerObject(object) {
        setAngle(m_angle);
    }

    void move(Vector2 amount);
    void moveTo(Vector2 position);

    void transform();
    void addAngle(float amount);
    void setAngle(float amount);
    float getAngle() const;

    void printVertices() const;

private:
    void calculateRectVertices();
    Vector2 rotate(Vector2 vector);

    float m_angle = 0;
    Object& m_ownerObject;
    bool m_hasTransformed;
    float m_sinValue;
    float m_cosValue;
};
} // namespace SE
