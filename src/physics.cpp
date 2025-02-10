#include <iostream>

#include "headers/objects.h"
#include "headers/physics.h"



void updateObject(Object& obj, float deltaTime) {

    // Update position: new position = initial position+(velocity×Δt)+1/2​×acceleration×(Δt)^2
    obj.position = obj.position + (obj.velocity * deltaTime) + obj.acceleration * (deltaTime * deltaTime )/ 2;

    // Update velocity: v = v + a * dt
    obj.velocity = obj.velocity + obj.acceleration * deltaTime;

}



//uses a = f/m to change the acceleration of an object
void applyForce(Object& obj, Vector2 force){

    obj.acceleration = force/obj.mass;

} 



void enableGravity(Object& obj) {
    obj.acceleration = obj.acceleration + GRAVITY; // Apply gravity to the y-component of acceleration
}


void detectCollision(Object &obj){
    for(auto instance : obj.instances){
        obj.detectCollisionAndUpdateVelocity();
    }
}