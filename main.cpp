#include <iostream>
#include <vector>
#include <unistd.h>
const float gravity = 9.8;


// Struct for a 2D vector (for position, velocity, or acceleration)
struct Vector2 {
    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}

    // Addition operator for Vector2
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // Subtraction operator for Vector2
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // Multiplication by a scalar
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // Division by a scalar
    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }
};


struct Object {

    Vector2 position;         // Position of the object
    Vector2 velocity;         // Velocity of the object
    Vector2 acceleration;     // Acceleration of the object
    float mass;

    Object() : position(0, 0), velocity(0, 0), acceleration(0, 0), mass(1) {}

    Object(float x, float y, float mass) 
        : position(x, y), velocity(0, 0), acceleration(0, 0), mass(mass) {}
};


void update(Object& obj, float deltaTime) {

    // Update position: new position = initial position+(velocity×Δt)+21​×acceleration×(Δt)^2
    obj.position = obj.position + (obj.velocity * deltaTime) + obj.acceleration * (deltaTime * deltaTime )/ 2;

    // Update velocity: v = v + a * dt
    obj.velocity = obj.velocity + obj.acceleration * deltaTime;

}


void applyGravity(Object& obj) {
    obj.acceleration.y = -gravity; // Apply gravity to the y-component of acceleration
}


int main(){

    Object obj(0, 0, 1.0f); // Create an object 
    float deltaTime = 1.0f; // Simulate Fps

    applyGravity(obj); // Apply gravity

    for (int i = 0; i < 100; ++i) {
        update(obj, deltaTime); // Update position and velocity

        std::cout << "Position: (" << obj.position.x << ", " << obj.position.y << ")" 
        << " velocity: (" << obj.velocity.x << ", " << obj.velocity.y << ")" 
         << " acceleration: (" << obj.acceleration.x << ", " << obj.acceleration.y << ")\n";


        sleep(1);
    }




    return 0;
}





