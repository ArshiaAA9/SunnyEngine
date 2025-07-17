#include "CircleObject.h"

namespace SE {

void CircleObject::checkValidDimensions() const {
    if (this->radius <= 0) {
        throw std::invalid_argument("Radius must be positive int.");
    }
}

float CircleObject::calculateInertia(float paramMass, float paramRadius) {
    // I = 1/2Mr^2
    float inertia = 1.0f / 2.0f * paramMass * paramRadius * paramRadius;
    // std::cout << "mass: " << paramMass << " radius:" << paramRadius << " circle inertia: " << inertia << '\n';
    return inertia;
}

void CircleObject::printProperties() const {
    Object::printProperties();
    std::cout << " Radius: " << this->radius << "\n";
}

ObjectType CircleObject::getType() const { return this->m_type; }

Dimensions CircleObject::getDimensions() const { return Dimensions(radius); }

void CircleObject::setMass(float mass) {
    m_mass = mass;
    m_inertia = calculateInertia(mass, radius);
}
} // namespace SE
