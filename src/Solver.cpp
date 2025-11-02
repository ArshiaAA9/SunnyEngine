#include "Solver.h"

#include "Physics.h"
#include "Types.h"
#include "Vector2.h"

// TODO: IMPLEMENT ANGULAR VELOCIRTY AND ROTATIONALA SOLVER
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
    if (vrel < 0) { // if negative mean objects are moving into each other so we only check that
        Vector2 j = calculateImpulse(pair, vrel);
        applyImpulse(pair, j);
    } else if (vrel == 0) {
        float massA = pair->objectA->getMass();
        float massB = pair->objectB->getMass();
        float totalMass = massA + massB;
        std::cout << " massA: " << massA << " massB: " << massB << " totalMass: " << totalMass
                  << " normal: " << pair->normal << " depth: " << pair->depth << '\n';

        Vector2 correctionA = pair->normal * (pair->depth * (massA / totalMass));
        Vector2 correctionB = pair->normal * (pair->depth * (massB / totalMass));

        // Position correction
        // std::cout << " correctionA: " << correctionA << " correctionB: " << correctionB << '\n';
        if (!pair->objectA->isStatic() && !pair->objectB->isStatic()) {
            // if none of them are static we do normal correction
            pair->objectA->transform.position += correctionA;
            pair->objectB->transform.position -= correctionB;
            return;
        }
        // need a way to calculate the normal other
    }
}

float Solver::calculateRelativeVelocity(CollisionPair* pair) {
    Vector2 v1 = pair->objectA->velocity;
    float w1 = pair->objectA->angularVelocity;
    Vector2 r1 = pair->r1;
    Vector2 v2 = pair->objectB->velocity;
    float w2 = pair->objectB->angularVelocity;
    Vector2 r2 = pair->r2;
    Vector2 normal = pair->normal;

    // w x r = (-w * r.y, w * r.x)

    Vector2 vrel = v1 + r1.cross(w1) - v2 - r2.cross(w2);
    return vrel.dotProduct(normal);
}

Vector2 Solver::calculateImpulse(CollisionPair* pair, float vrel) {
    // j = (-(1+e) vAB1 . n) / ((n.n) (1/m1 + 1/m2) + (rAP.n)^2/IA + (rBP . n)^2/IB)
    // e is 1 because of rigid bodies
    // for adding non rigid bodies modify the function to count in the e of the object
    //
    float invertM1 = pair->objectA->getInvertedMass();
    float invertM2 = pair->objectB->getInvertedMass();
    float invertI1 = pair->objectA->getInvertedInertia();
    float invertI2 = pair->objectB->getInvertedInertia();
    Vector2 r1 = pair->r1;
    Vector2 r2 = pair->r2;
    Vector2 normal = pair->normal;
    float e = pair->averageRestitution;

    float r1CrossNormal = r1.crossProduct(normal);
    float r2CrossNormal = r2.crossProduct(normal);

    float impulse = -(1.0f + e) * vrel;
    impulse /=
        invertM1 + invertM2 + invertI1 * r1CrossNormal * r1CrossNormal + invertI2 * r2CrossNormal * r2CrossNormal;

    return normal * impulse;
}

void Solver::applyImpulse(CollisionPair* pair, Vector2 impulse) {
    ObjectPtr obj1 = pair->objectA;
    ObjectPtr obj2 = pair->objectB;
    Vector2 r1 = pair->r1;
    Vector2 r2 = pair->r2;

    obj1->velocity += impulse * obj1->getInvertedMass();
    obj2->velocity -= impulse * obj2->getInvertedMass();

    obj1->angularVelocity += r1.crossProduct(impulse) * obj1->getInvertedInertia();
    obj2->angularVelocity -= r2.crossProduct(impulse) * obj2->getInvertedInertia();
}
} // namespace SE
