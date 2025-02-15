#include "headers/Physics.h"
#include "headers/Objects.h"
#include "Physics.h"

void PhysicsWorld::addObject(Object* object){ 
        m_objects.push_back(object);
    }

void PhysicsWorld::removeObject(Object* object){
        //if nullptr
        if(!object) return;
        auto itr = std::find(m_objects.begin(), m_objects.end(), object);
        if (itr == m_objects.end()) return;
        m_objects.erase(itr);
}

std::vector<Object*> PhysicsWorld::getObjects(){
    return m_objects;
}

void PhysicsWorld::step(float dt){
        //updates the simulation every dt
		for (Object* obj : m_objects) {
			obj->force += m_gravity * obj->mass; // apply a force
 
			obj->velocity += obj->force / obj->mass * dt;
			obj->transform.position += obj->velocity * dt;
 
			obj->force = Vector2(0, 0); // reset net force at the end
		}
	}

void PhysicsWorld::setGravity(Vector2 gravity){
        m_gravity = gravity;
}
