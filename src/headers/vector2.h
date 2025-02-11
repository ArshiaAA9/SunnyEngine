#pragma once

#include <iostream>


// Struct for a 2D vector (for position, velocity, or acceleration)
struct Vector2 {

    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}



    // Addition operator for Vector2
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // += operator for vector2
    void operator+=(const Vector2& other){
        x += other.x; y += other.y;
    }



    // Subtraction operator for Vector2
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // cases let vector(x, y) -vector = vector(-x, -y) 
    Vector2 operator-(){
        return Vector2(-x, -y);
    }

    // -= operator for vector2
    void operator+=(const Vector2& other){
        x -= other.x; y -= other.y;
    }


    // Multiplication by a scalar
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }


    // Division by a scalar
    Vector2 operator/(float scalar) const {
        if(scalar == 0){
            throw std::invalid_argument("scalar must be non-zero.");
        }
        return Vector2(x / scalar, y / scalar);
    }


    friend Vector2 operator*(float scalar, const Vector2& vector);
    friend Vector2 operator/(float scalar, const Vector2& vector);

};

