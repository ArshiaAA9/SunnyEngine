#include "headers/Solver.h"

#include <iostream>

#include "headers/Physics.h"
#include "headers/Vector2.h"

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
    }
    // position correction for when 2 objects have same velocity and coliding
    float massA = pair->objectA->mass;
    float massB = pair->objectB->mass;
    float totalMass = massA + massB;

    Vector2 correctionA = pair->normal * (pair->depth * (pair->objectB->mass / totalMass));
    Vector2 correctionB = pair->normal * (pair->depth * (pair->objectA->mass / totalMass));

    // Position correction
    pair->objectA->transform.position += correctionA;
    pair->objectB->transform.position -= correctionB;
}

float Solver::calculateRelativeVelocity(CollisionPair* pair) {
    Vector2 v1 = pair->objectA->velocity;
    Vector2 v2 = pair->objectB->velocity;
    Vector2 normal = pair->normal;
    Vector2 vrel = v1 - v2;
    return vrel.dotProduct(normal);
}

Vector2 Solver::calculateImpulse(CollisionPair* pair, float vrel) {
    float m1 = pair->objectA->mass;
    float m2 = pair->objectB->mass;
    Vector2 normal = pair->normal;

    float impulse = -2 * vrel;
    impulse /= 1 / m1 + 1 / m2;

    return normal * impulse;
}

void Solver::applyImpulse(CollisionPair* pair, Vector2 impulse) {
    Vector2 force = impulse;
    Object* obj1 = pair->objectA;
    Object* obj2 = pair->objectB;
    std::cout << " impulse: " << impulse.x << ',' << impulse.y << '\n';

    obj1->velocity += impulse / obj1->mass;
    obj2->velocity -= impulse / obj2->mass;
}
