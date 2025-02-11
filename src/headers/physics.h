#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "vector2.h"
#include "objects.h"

class PhysicsWorld {
private:

    std::vector<Object*> m_objects;
    Vector2 m_gravity = Vector2(0, -9.81);

public:

    void addObject(Object* object){ 
        m_objects.push_back(object);
    }
    void removeObject(Object* object){
        //if nullptr
        if(!object) return;
        auto itr = std::find(m_objects.begin(), m_objects.end(), object);
        if (itr == m_objects.end()) return;
        m_objects.erase(itr);
    }


    void step(float dt){
        //updates the simulation every dt
		for (Object* obj : m_objects) {
			obj->Force += obj->Mass * m_gravity; // apply a force
 
			obj->Velocity += obj->Force / obj->Mass * dt;
			obj->Position += obj->Velocity * dt;
 
			obj->Force = Vector2(0, 0); // reset net force at the end
		}
	}


    void setGravity(Vector2 gravity){
        m_gravity = gravity;
    }
};





