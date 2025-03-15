#pragma once

#include <math.h>

#include <iostream>

// Struct for a 2D vector (for position, velocity, or acceleration)
struct Vector2 {

    float x, y;

    Vector2()
        : x(0)
        , y(0) {}

    Vector2(float x, float y)
        : x(x)
        , y(y) {}

    Vector2 operator+(const Vector2& other) const;
    void operator+=(const Vector2& other);

    Vector2 operator-(const Vector2& other) const;
    void operator-=(const Vector2& other);

    // Multiplications:

    // Multiplication by a scalar
    Vector2 operator*(float scalar) const;
    void operator*=(float scalar);

    // Multiplication by vector
    Vector2 componentProduct(const Vector2& vector);
    void componentProductUpdate(const Vector2& vector);
    // Scalar Product (Dot Product) A.B
    float dotProduct(const Vector2& vector);

    // Cross Product A x B = ax * by - ay * bx
    float crossProduct(const Vector2& vector);

    // Divisions:

    // Division by a scalar
    Vector2 operator/(float scalar);
    void operator/=(float scalar);

    bool operator<(const Vector2& other) const;
    bool operator>(Vector2& other) const;

    void addScaledVector2(float scale, const Vector2& vector);

    // Methods:

    void invert();

    float magnitude() const;

    float squaredMagnitude();

    void normalize();

    float squaredLengthOf2Pos(const Vector2 vector) const;
    float lengthOf2Pos(const Vector2 vector) const;

private:
    void checkScalar(float scalar);
};
