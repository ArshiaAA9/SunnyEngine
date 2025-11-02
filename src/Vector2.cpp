#include "Vector2.h"

#include <iostream>

namespace SE {
Vector2 Vector2::operator+(const Vector2& other) const {
    // Addition operator for Vector2
    return Vector2(x + other.x, y + other.y);
}

void Vector2::operator+=(const Vector2& other) {
    // += operator for vector2
    x += other.x;
    y += other.y;
}

Vector2 Vector2::operator-(const Vector2& other) const {
    // Subtraction operator for Vector2
    return Vector2(x - other.x, y - other.y);
}

void Vector2::operator-=(const Vector2& other) {
    // -= operator for vector2
    x -= other.x;
    y -= other.y;
}

Vector2 Vector2::operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }

void Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
}

Vector2 Vector2::componentProduct(const Vector2& vector) {
    // Vector2(x1 * x2, y1 * y2)
    return Vector2(vector.x * x, vector.y * y);
}

void Vector2::componentProductUpdate(const Vector2& vector) {
    // x1 *= x2 example
    x *= vector.x;
    y *= vector.y;
}

float Vector2::dotProduct(const Vector2& vector) { return x * vector.x + y * vector.y; }

float Vector2::crossProduct(const Vector2& vector) { return x * vector.y - y * vector.x; }

Vector2 Vector2::cross(float s) { return Vector2(-s * this->y, s * this->x); }

Vector2 Vector2::operator/(float scalar) {
    checkScalar(scalar);
    return Vector2(x / scalar, y / scalar);
}

void Vector2::operator/=(float scalar) {
    checkScalar(scalar);
    x /= scalar;
    y /= scalar;
}

bool Vector2::operator<(const Vector2& other) const {
    if (x < other.x) return true;                 // Compare x components first
    if (x == other.x && y < other.y) return true; // If x is equal, compare y
    return false;
}

bool Vector2::operator>(Vector2& other) const {
    if (x > other.x && y > other.y) return true;
    else
        return false;
}

void Vector2::addScaledVector2(float scale, const Vector2& vector) {
    // a + bc
    x += vector.x * scale;
    y += vector.y * scale;
}

void Vector2::invert() {
    x = -x;
    y = -y;
}

float Vector2::magnitude() const { return sqrt(x * x + y * y); }

float Vector2::squaredMagnitude() { return x * x + y * y; }

void Vector2::normalize() {
    float length = magnitude();
    if (length > 0) {
        *this /= length;
    }
}

float Vector2::squaredLengthOf2Pos(const Vector2 vector) const {
    // find squared length of 2 position used in formulas to calculate distance
    float dx = x - vector.x;
    float dy = y - vector.y;
    return dx * dx + dy * dy;
}

float Vector2::lengthOf2Pos(const Vector2 vector) const {
    // find length of 2 position used in formulas to calculate distance
    float dx = x - vector.x;
    float dy = y - vector.y;
    return sqrt(dx * dx + dy * dy);
}

void Vector2::checkScalar(float scalar) {
    // used to avoid division by 0 in scalar division
    if (scalar == 0) {
        throw std::invalid_argument("scalar must be non-zero.");
    }
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
    os << "(" << vec.x << ',' << vec.y << ')';
    return os;
}

} // namespace SE
