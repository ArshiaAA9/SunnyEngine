#include "RectObject.h"

namespace SE {
// Objects Base private Methods:
float RectObject::calculateInertia(float paramMass, float paramWidth, float paramHeight) {
    // Ic = 1/12m(h^2 + w^2))
    float inertia = 1.0f / 12.0f * paramMass * (paramHeight * paramHeight + paramWidth * paramWidth);
    // std::cout << "mass: " << paramMass << " paramHeight: " << paramHeight << " paramWidth: " << paramWidth
    //           << " rect inertia: " << inertia << '\n';
    return inertia;
}

void RectObject::printProperties() const {
    Object::printProperties();
    std::cout << " Dimensions: " << this->m_width << "," << this->m_height << "\n";
}

void RectObject::checkValidDimensions() const {
    if (this->m_height <= 0 || this->m_width <= 0) {
        throw std::invalid_argument("m_height, and m_width must be positive int.");
    }
}

Dimensions RectObject::getDimensions() const { return Dimensions(m_width, m_height); }

void RectObject::setMass(float mass) {
    m_mass = mass;
    m_inertia = calculateInertia(m_mass, m_width, m_height);
}
} // namespace SE
