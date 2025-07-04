#include "headers/RectObject.h"

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
    std::cout << " Dimensions: " << this->width << "," << this->height << "\n";
}

void RectObject::checkValidDimensions() const {
    if (this->height <= 0 || this->width <= 0) {
        throw std::invalid_argument("Height, and width must be positive int.");
    }
}

// getType pure virtual function:
ObjectType RectObject::getType() const { return this->type; }

// getDimensions pure virtual function:
/**@return Dimensions(width, height)*/
Dimensions RectObject::getDimensions() const { return Dimensions(width, height); }
} // namespace SE
