#include "headers/CollisionDetection.h"

#include <algorithm>
#include <cmath>

#include "headers/GridPartition.h"
#include "headers/Objects.h"
#include "headers/Vector2.h"

// FIX: fix this abomination
void CollisionDetection::checkCollision() {
    int rows = m_grid->getRowCount();
    int cols = m_grid->getColCount();
}

// used inside checkCollision function
void CollisionDetection::checkCollisionByType(Object* obj1, Object* obj2) {
    if (obj1->type == Object::RECT && obj2->type == Object::RECT) { // Rect-Rect
        RectObject* r1 = dynamic_cast<RectObject*>(obj1);
        RectObject* r2 = dynamic_cast<RectObject*>(obj2);
        clRectRect(*r1, *r2);

    } else if (obj1->type == Object::CIRCLE && obj2->type == Object::CIRCLE) { // Circle-Circle
        CircleObject* c1 = dynamic_cast<CircleObject*>(obj1);
        CircleObject* c2 = dynamic_cast<CircleObject*>(obj2);
        clCircleCircle(*c1, *c2);

    } else if (
        (obj1->type == Object::RECT && obj2->type == Object::CIRCLE) ||
        (obj1->type == Object::CIRCLE && obj2->type == Object::RECT)) { // Rect-Circle or Circle-Rect

        // Ensure the first object is always the circle
        if (obj1->type == Object::CIRCLE) {
            CircleObject* c = dynamic_cast<CircleObject*>(obj1);
            RectObject* r = dynamic_cast<RectObject*>(obj2);
            clCircleRect(*c, *r);

        } else {
            RectObject* r = dynamic_cast<RectObject*>(obj1);
            CircleObject* c = dynamic_cast<CircleObject*>(obj2);
            clCircleRect(*c, *r);
        }
    }
}

void CollisionDetection::clCircleCircle(CircleObject& c1, CircleObject& c2) {
    float squaredDistance = c1.transform.position.squaredLengthOf2Pos(c2.transform.position);

    // a collision is found
    if (squaredDistance <= (c1.radius + c2.radius) * (c1.radius + c2.radius)) {
        float depth = (c1.radius - c2.radius) - std::sqrt(squaredDistance);

        // calculating pointA pointB:
        Vector2 direction = c2.transform.position - c1.transform.position; // finding direction from c1 to c2
        direction.normalize();                                             // normalizing the vector

        Vector2 pointA = c1.transform.position - direction * c1.radius;
        Vector2 pointB = c2.transform.position - direction * c2.radius;
        addClPair(&c1, pointA, &c2, pointB, depth);
    }
}

// Circle vs. Rectangle Collision Detection
void CollisionDetection::clCircleRect(CircleObject& c, RectObject& rect) {
    Vector2 cPos = c.transform.position;
    Vector2 rectPos = rect.transform.position;
    float r = c.radius;

    float rectLeft = rectPos.x - rect.width / 2.0f;
    float rectRight = rectPos.x + rect.width / 2.0f;
    float rectTop = rectPos.y + rect.height / 2.0f;
    float rectBottom = rectPos.y - rect.height / 2.0f;

    // Closest point on rectangle to circle center
    float px = std::clamp(cPos.x, rectLeft, rectRight);
    float py = std::clamp(cPos.y, rectBottom, rectTop);
    Vector2 p = Vector2(px, py);

    Vector2 direction = cPos - p;
    float distanceSquared = direction.squaredMagnitude();

    // if distance < r collision is happening
    if (distanceSquared < r * r) {
        float penDepth = r - std::sqrt(distanceSquared);
        direction.normalize();

        Vector2 pointA = cPos - direction * r;
        Vector2 pointB = p;
        addClPair(&c, pointA, &rect, pointB, penDepth);
    }
}

bool CollisionDetection::aabb(RectObject& r1, RectObject& r2) {
    Vector2 r1Pos = r1.transform.position;
    Vector2 r2Pos = r2.transform.position;

    float r1Left = r1Pos.x - r1.width / 2.0f;
    float r1Right = r1Pos.x + r1.width / 2.0f;
    float r1Top = r1Pos.y + r1.height / 2.0f;
    float r1Bot = r1Pos.y - r1.height / 2.0f;

    float r2Left = r2Pos.x - r2.width / 2.0f;
    float r2Right = r2Pos.x + r2.width / 2.0f;
    float r2Top = r2Pos.y + r2.height / 2.0f;
    float r2Bot = r2Pos.y - r2.height / 2.0f;

    return (r1Left <= r2Right && r1Right >= r2Left && r1Bot <= r2Top && r1Top >= r2Bot);
}

void CollisionDetection::clRectRect(RectObject& r1, RectObject& r2) {
    if (aabb(r1, r2)) {
        float r1Left = r1.transform.position.x - r1.width / 2.0f;
        float r1Right = r1.transform.position.x + r1.width / 2.0f;
        float r1Top = r1.transform.position.y + r1.height / 2.0f;
        float r1Bot = r1.transform.position.y - r1.height / 2.0f;

        float r2Left = r2.transform.position.x - r2.width / 2.0f;
        float r2Right = r2.transform.position.x + r2.width / 2.0f;
        float r2Top = r2.transform.position.y + r2.height / 2.0f;
        float r2Bot = r2.transform.position.y - r2.height / 2.0f;

        // Calculate overlap on both axes
        float overlapX = std::min(r1Right, r2Right) - std::max(r1Left, r2Left);
        float overlapY = std::min(r1Top, r2Top) - std::max(r1Bot, r2Bot);

        Vector2 pointA, pointB;
        float penDepth;
        // the collision is primarly on smaller overlap
        if (overlapX < overlapY) { // if X axis collision:
            if (r1.transform.position.x > r2.transform.position.x) {
                pointA = Vector2(r1Left, r1.transform.position.y);
                pointB = Vector2(r2Right, r2.transform.position.y);
            } else {
                pointA = Vector2(r1Right, r1.transform.position.y);
                pointB = Vector2(r2Left, r2.transform.position.y);
            }
            penDepth = overlapX;
        } else {
            if (r1.transform.position.y > r2.transform.position.y) { // if Y axis collision:
                pointA = Vector2(r1.transform.position.x, r1Bot);
                pointB = Vector2(r2.transform.position.x, r2Top);
            } else {
                pointA = Vector2(r1.transform.position.x, r1Top);
                pointB = Vector2(r2.transform.position.x, r2Bot);
            }
            penDepth = overlapY;
        }
        addClPair(&r1, pointA, &r2, pointB, penDepth);
    }
}
void CollisionDetection::addClPair(Object* obj1, Vector2 pointA, Object* obj2, Vector2 pointB, float depth) {
    CollisionPair* collision = new CollisionPair(obj1, pointA, obj2, pointB, depth);
    m_collisionPairs.push_back(collision);
}

void CollisionDetection::deleteClPair(CollisionPair* pair) {
    if (!pair) return;
    auto itr = std::find(m_collisionPairs.begin(), m_collisionPairs.end(), pair);
    if (itr == m_collisionPairs.end()) return;
    m_collisionPairs.erase(itr);
    delete pair;
    pair = nullptr;
}

std::vector<CollisionPair*>* CollisionDetection::getClPairsptr() { return &m_collisionPairs; }
