#include "headers/Solver.h"

#include "headers/Physics.h"
#include "headers/Types.h"
#include "headers/Vector2.h"

// TODO: IMPLEMENT ANGULAR VELOCIRTY AND ROTATIONALA SOLVER
// FIX: SOLVER A BIT GLITCHY
namespace SE {
void Solver::solveCollisionPairs() {
    auto& clPairs = m_world.cD.getClPairs();
    for (auto& pair : clPairs) {
        if (pair) {
            CollisionPair* pPair = pair.get();
            solve(pPair);
            m_world.cD.deleteClPair(pPair);
        }
    }
}

void Solver::solve(CollisionPair* pair) {
    float vrel = calculateRelativeVelocity(pair);
    if (vrel < 0) { // if negative mean objects are moving into each other
        Vector2 j = calculateImpulse(pair, vrel);
        applyImpulse(pair, j);
    } else if (vrel == 0) {
        float massA = pair->objectA->mass;
        float massB = pair->objectB->mass;
        float totalMass = massA + massB;

        Vector2 correctionA = pair->normal * (pair->depth * (pair->objectB->mass / totalMass));
        Vector2 correctionB = pair->normal * (pair->depth * (pair->objectA->mass / totalMass));

        // Position correction
        pair->objectA->transform.position += correctionA;
        pair->objectB->transform.position -= correctionB;
        // }
    }
}

float Solver::calculateRelativeVelocity(CollisionPair* pair) {
    Vector2 v1 = pair->objectA->velocity;
    Vector2 v2 = pair->objectB->velocity;
    Vector2 normal = pair->normal;
    Vector2 vrel = v1 - v2;
    return vrel.dotProduct(normal);
}

Vector2 Solver::calculateImpulse(CollisionPair* pair, float vrel) {
    float invertM1 = pair->objectA->invertedMass;
    float invertM2 = pair->objectB->invertedMass;
    Vector2 normal = pair->normal;

    float impulse = -2.0f * vrel; // -2 cause all bodies are elastic
    impulse /= invertM1 + invertM2;

    return normal * impulse;
}

void Solver::applyImpulse(CollisionPair* pair, Vector2 impulse) {
    ObjectPtr obj1 = pair->objectA;
    ObjectPtr obj2 = pair->objectB;
    // std::cout << " impulse: " << impulse.x << ',' << impulse.y << '\n';

    obj1->velocity += impulse * obj1->invertedMass;
    obj2->velocity -= impulse * obj2->invertedMass;
}
} // namespace SE
