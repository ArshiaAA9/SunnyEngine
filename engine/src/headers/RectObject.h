#pragma once

#include "Objects.h"

namespace SE {
class RectObject : public Object {
public:
    // constructor:
    RectObject(float x, float y, float mass, float width, float height)
        : Object(x, y, mass, ObjectType::RECT, calculateInertia(mass, width, height))
        , m_height(height)
        , m_width(width) {
        checkValidDimensions();
        this->transform.vertices = {
            Vector2(-width / 2, height / 2), Vector2(-width / 2, -height / 2), Vector2(width / 2, -height / 2),
            Vector2(width / 2, height / 2)};
        this->transform.transformedVertices.resize(4);
    }

    RectObject(float x, float y, float width, float height)
        : Object(x, y, ObjectType::RECT, calculateInertia(0, width, height))
        , m_height(height)
        , m_width(width) {
        checkValidDimensions();
        this->transform.vertices = {
            Vector2(-width / 2, height / 2), Vector2(-width / 2, -height / 2), Vector2(width / 2, -height / 2),
            Vector2(width / 2, height / 2)};
        this->transform.transformedVertices.resize(4);
    }

    ~RectObject() = default;

    Dimensions getDimensions() const override;
    ObjectType getType() const;
    void printProperties() const override;

private:
    void checkValidDimensions() const;
    float calculateInertia(float mass, float width, float height);
    void setMass(float mass) override;

    int m_height;
    int m_width;
};
} // namespace SE
