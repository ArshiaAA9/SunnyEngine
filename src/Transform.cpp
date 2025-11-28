#include "Transform.h"

namespace SE {

// publics:

void Transform::move(Vector2 amount) {
    this->position += amount;
    this->m_hasTransformed = false;
}

void Transform::moveTo(Vector2 position) {
    this->position = position;
    m_hasTransformed = false;
}

void Transform::transform() {
    // go over vertices and transform them
    if (m_hasTransformed == false) {
        for (size_t i = 0; i < transformedVertices.size(); i++) {
            transformedVertices[i] = rotate(vertices[i]) + position;
        }
        m_hasTransformed = true;
    }
}

void Transform::addAngle(float amount) {
    this->m_angle += amount;
    this->m_sinValue = std::sin(this->m_angle);
    this->m_cosValue = std::cos(this->m_angle);
    this->m_hasTransformed = false;
}

void Transform::setAngle(float amount) {
    this->m_angle = amount;
    this->m_sinValue = std::sin(this->m_angle);
    this->m_cosValue = std::cos(this->m_angle);
    this->m_hasTransformed = false;
}

void Transform::printVertices() const {
    std::cout << "1.vertices: " << this->transformedVertices[0] << '\n'
              << "2.vertices: " << this->transformedVertices[1] << '\n'
              << "3.vertices: " << this->transformedVertices[2] << '\n'
              << "4.vertices: " << this->transformedVertices[3] << std::endl;
}

// private:

Vector2 Transform::rotate(Vector2 vector) {
    // x1 = x0cos(θ) – y0sin(θ)(Equation 1)
    // y1 = x0sin(θ) + y0cos(θ)(Equation 2)

    float rx = vector.x * this->m_cosValue - vector.y * this->m_sinValue;
    float ry = vector.x * this->m_sinValue + vector.y * this->m_cosValue;

    return Vector2(rx, ry);
}

float Transform::getAngle() const { return m_angle; }

} // namespace SE
