#include "headers/vector2.h"

// Friend function definition
Vector2 operator*(float scalar, const Vector2& vector) {
    return Vector2(vector.x * scalar, vector.y * scalar);
}


Vector2 operator/(float scalar, const Vector2& vector) {
    return Vector2(vector.x / scalar, vector.y / scalar);
}