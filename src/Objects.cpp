#include "Objects.h"

#include <iostream>

namespace SE {

// Objects Base Functions:
void Object::applyForce(Vector2 force) { this->force += force; }

void Object::setForce(Vector2 force) { this->force = force; }

void Object::applyTorque(float torque) { this->torque += torque; }

void Object::setTorque(float torque) { this->torque = torque; }

void Object::addVelocity(Vector2 velocity) { this->velocity += velocity; }

void Object::setVelocity(Vector2 velocity) { this->velocity = velocity; }

void Object::addAngularVelocity(float angularVelocity) { this->angularVelocity += angularVelocity; }

void Object::setAngularVelocity(float angularVelocity) { this->angularVelocity = angularVelocity; }

// printProperties() virtual function:
void Object::printProperties() const {
    std::cout << "Position: (" << this->transform.position.x << ", " << this->transform.position.y << ")"
              << " Velocity: (" << this->velocity.x << ", " << this->velocity.y << ")"
              << " Force: (" << this->force.x << ", " << this->force.y << ")";
}

void Object::checkValidValues() const {
    if (!m_isStatic) {
        if (this->m_mass <= 0.0f) throw std::invalid_argument("Mass must be positive value");
    }
    if (!(0 <= m_restitution && m_restitution <= 1)) {
        std::cerr << "error: coeffisient of restitution should be withing 0 and 1";
    }
}

float Object::getInvertedInertia() const { return m_invertedInertia; }

float Object::getInertia() const { return m_inertia; }

float Object::getMass() const { return m_mass; }

ObjectType Object::getType() const { return m_type; }

bool Object::isStatic() const { return m_isStatic; }

float Object::getInvertedMass() const { return m_invertedMass; }

float Object::getRestitution() const { return m_restitution; }

} // namespace SE
