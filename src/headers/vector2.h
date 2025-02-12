#pragma once

#include <math.h>
#include <iostream>


// Struct for a 2D vector (for position, velocity, or acceleration)
struct Vector2 {

    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}



    Vector2 operator+(const Vector2& other) const {
        // Addition operator for Vector2
        return Vector2(x + other.x, y + other.y);
    }
    void operator+=(const Vector2& other){
        // += operator for vector2
        x += other.x; y += other.y;
    }


    Vector2 operator-(const Vector2& other) const {
        // Subtraction operator for Vector2
        return Vector2(x - other.x, y - other.y);
    }
    void operator-=(const Vector2& other){
        // -= operator for vector2
        x -= other.x; y -= other.y;
    }



    // Multiplications:

    // Multiplication by a scalar
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Multiplication by vector
    Vector2 componentProduct(const Vector2& vector){
        //Vector2(x1 * x2, y1 * y2)
       return Vector2(vector.x * x, vector.y * y);
    }
    void componentProductUpdate(const Vector2& vector){
        //x1 *= x2 example
        x *= vector.x;
        y *= vector.y;
    }

    // Scalar Product (Dot Product) A.B 
    float dotProduct(const Vector2& vector){
        return x * vector.x + y * vector.y;
    }

    // Cross Product A x B = ax * by - ay * bx
    float crossProduct(const Vector2& vector){
        return x * vector.y - y * vector.x;
    }



    // Divisions:

    // Division by a scalar
    Vector2 operator/(float scalar) const {
        checkScalar(scalar);
        return Vector2(x / scalar, y / scalar);
    }
    Vector2& operator/=(float scalar){
        
        checkScalar(scalar);
        x /= scalar;
        y /= scalar;
        return *this;
    }



    bool operator<(const Vector2& other) const {
        if (x < other.x) return true;   // Compare x components first
        if (x == other.x && y < other.y) return true;  // If x is equal, compare y
        return false;
    }
    bool operator>(Vector2& other)const{
        if(x > other.x && y > other.y) return true;
        else return false;
    }


    void addScaledVector2(float scale, const Vector2& vector){
        //a + bc
        x += vector.x * scale;
        y += vector.y * scale;
    }



    // Methods:

    void invert(){
        x = -x;
        y = -y;
    }

    float magnitude() const {
        return sqrt(x*x + y*y);
    }

    float squaredMagnitude(){
        return x*x + y*y;
    }

    void normalize(){
        float length = magnitude();
        if(length > 0){
            (*this)*= ((float)1)/length;
        }
    }

    float squaredLengthOf2Pos(const Vector2 vector) const {
        //find squared length of 2 Position used in formulas to calculate distance
        float dx = x - vector.x;
        float dy = y - vector.y;
        return dx * dx + dy * dy;
    }
    float lengthOf2Pos(const Vector2 vector) const {
        //find length of 2 Position used in formulas to calculate distance
        float dx = x - vector.x;
        float dy = y - vector.y;
        return sqrt(dx * dx + dy * dy);
    }

private:
    void checkScalar(scalar){
        //used to avoid division by 0 in scalar division
        if(scalar == 0){
            throw std::invalid_argument("scalar must be non-zero.");
        }
    }
};

