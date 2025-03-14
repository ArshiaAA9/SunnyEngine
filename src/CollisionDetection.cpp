#include "headers/CollisionDetection.h"

#include <algorithm>
#include <iostream>
#include <memory>

#include "headers/CollisionPair.h"
#include "headers/GridPartition.h"
#include "headers/Objects.h"
#include "headers/Vector2.h"

/**@brief Performs collision detection using a spatial grid partitioning system.
 * @brief Iterates through all grid cells, checks collisions between objects within the same cell,
 * @brief and between objects in neighboring cells to handle boundary/cross-cell collisions.*/
void CollisionDetection::checkCollisions() {
    // Get grid dimensions
    int rowCount = m_grid.getRowCount();
    int colCount = m_grid.getColCount();

    // Iterate through all cells in the grid
    for (int col = 0; col < colCount; col++) {
        for (int row = 0; row < rowCount; row++) {

            // Get reference to objects in current cell
            auto& objectsInCell = m_grid.getObjectInCell(col, row);

            // Skip empty cells to optimize processing
            if (objectsInCell.empty()) continue;

            // Check collisions between all unique pairs in current cell
            // Uses i/j nested loops to avoid duplicate checks (A-B vs B-A)
            for (size_t i = 0; i < objectsInCell.size(); i++) {
                for (size_t j = i + 1; j < objectsInCell.size(); j++) {
                    Object* obj1 = objectsInCell[i];
                    Object* obj2 = objectsInCell[j];
                    std::cout << " Object1&: " << obj1 << " Object2&: " << obj2 << '\n';
                    m_grid.logAllObjects();
                    if (obj1 && obj2) checkCollisionByType(obj1, obj2);
                }
            }

            // Check collisions with objects in neighboring cells
            // Iterates through 8 surrounding cells
            for (int dcol = -1; dcol <= 1; dcol++) {
                for (int drow = -1; drow <= 1; drow++) {
                    // Skip current cell
                    if (dcol == 0 && drow == 0) continue;

                    // Calculate neighbor cell coordinates
                    int neighborCol = col + dcol;
                    int neighborRow = row + drow;

                    // Validate neighbor cell boundaries
                    if (neighborCol >= 0 && neighborCol < colCount && neighborRow >= 0 && neighborRow < rowCount) {

                        // Get reference to neighbor cell objects
                        auto& pNeighborObjectsInCell = m_grid.getObjectInCell(neighborCol, neighborRow);

                        // Check all object pairs between current and neighbor cell
                        for (auto& obj1 : objectsInCell) {
                            for (auto& obj2 : pNeighborObjectsInCell) {
                                checkCollisionByType(obj1, obj2); // .get() to get pointers to object from unique_ptr
                            }
                        }
                    }
                }
            }
        }
    }
}

// used inside checkCollision function
void CollisionDetection::checkCollisionByType(Object* obj1, Object* obj2) {
    if (obj1->getType() == RECT && obj2->getType() == RECT) { // Rect-Rect
        clRectRect(obj1, obj2);

    } else if (obj1->getType() == CIRCLE && obj2->getType() == CIRCLE) { // Circle-Circle
        clCircleCircle(obj1, obj2);

    } else if (
        (obj1->getType() == RECT && obj2->getType() == CIRCLE) ||
        (obj1->getType() == CIRCLE && obj2->getType() == RECT)) { // Rect-Circle or Circle-Rect

        // Ensure the first object is always the circle
        if (obj1->type == CIRCLE) {
            clCircleRect(obj1, obj2);

        } else {
            clCircleRect(obj2, obj1);
        }
    }
}

void CollisionDetection::clCircleCircle(Object* c1, Object* c2) {
    float squaredDistance = c1->transform.position.squaredLengthOf2Pos(c2->transform.position);
    float c1r = c1->getDimensions().x;
    float c2r = c2->getDimensions().x;
    // a collision is found
    if (squaredDistance <= (c1r + c2r) * (c1r + c2r)) {
        float depth = (c1r + c2r) - std::sqrt(squaredDistance); // Correct formula

        // calculating pointA pointB:
        Vector2 direction = c2->transform.position - c1->transform.position; // finding direction from c1 to c2
        direction.normalize();                                               // normalizing the vector

        Vector2 pointA = c1->transform.position - direction * c1r;
        Vector2 pointB = c2->transform.position - direction * c2r;
        addClPair(c1, pointA, c2, pointB, depth);
    }
}

// Circle vs. Rectangle Collision Detection
void CollisionDetection::clCircleRect(Object* c, Object* rect) {
    Vector2 cPos = c->transform.position;
    Vector2 rectPos = rect->transform.position;
    float r = c->getDimensions().x;
    float halfWidth = rect->getDimensions().x / 2.0f;
    float halfHeight = rect->getDimensions().y / 2.0f;

    float rectLeft = rectPos.x - halfWidth;
    float rectRight = rectPos.x + halfWidth;
    float rectTop = rectPos.y + halfHeight;
    float rectBottom = rectPos.y - halfHeight;

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
        addClPair(c, pointA, rect, pointB, penDepth);
    }
}

bool CollisionDetection::aabb(Object* r1, Object* r2) {
    Vector2 r1Pos = r1->transform.position;
    Vector2 r2Pos = r2->transform.position;

    float halfWidth1 = r1->getDimensions().x / 2.0f;
    float halfHeight1 = r1->getDimensions().y / 2.0f;

    float halfWidth2 = r2->getDimensions().x / 2.0f;
    float halfHeight2 = r2->getDimensions().y / 2.0f;

    float r1Left = r1Pos.x - halfWidth1;
    float r1Right = r1Pos.x + halfWidth1;
    float r1Top = r1Pos.y + halfHeight1;
    float r1Bot = r1Pos.y - halfHeight1;

    float r2Left = r2Pos.x - halfWidth2;
    float r2Right = r2Pos.x + halfWidth2;
    float r2Top = r2Pos.y + halfHeight2;
    float r2Bot = r2Pos.y - halfHeight2;

    return (r1Left <= r2Right && r1Right >= r2Left && r1Bot <= r2Top && r1Top >= r2Bot);
}

void CollisionDetection::clRectRect(Object* r1, Object* r2) {
    if (aabb(r1, r2)) {
        Vector2 r1pos = r1->transform.position;
        Vector2 r2pos = r2->transform.position;

        float r1halfWidth = r1->getDimensions().x / 2.0f;
        float r1halfHeight = r1->getDimensions().y / 2.0f;

        float r2halfWidth = r2->getDimensions().x / 2.0f;
        float r2halfHeight = r2->getDimensions().y / 2.0f;

        float r1Left = r1->transform.position.x - r1halfWidth;
        float r1Right = r1->transform.position.x + r1halfWidth;
        float r1Top = r1->transform.position.y + r1halfHeight;
        float r1Bot = r1->transform.position.y - r1halfHeight;

        float r2Left = r2->transform.position.x - r2halfWidth;
        float r2Right = r2->transform.position.x + r2halfWidth;
        float r2Top = r2->transform.position.y + r2halfHeight;
        float r2Bot = r2->transform.position.y - r2halfHeight;

        // Calculate overlap on both axes
        float overlapX = std::min(r1Right, r2Right) - std::max(r1Left, r2Left);
        float overlapY = std::min(r1Top, r2Top) - std::max(r1Bot, r2Bot);

        Vector2 pointA, pointB;
        float penDepth;
        // the collision is primarily on smaller overlap
        if (overlapX < overlapY) { // if X axis collision:
            if (r1pos.x > r2pos.x) {
                pointA = Vector2(r1Left, r1pos.y);
                pointB = Vector2(r2Right, r2pos.y);
            } else {
                pointA = Vector2(r1Right, r1pos.y);
                pointB = Vector2(r2Left, r2pos.y);
            }
            penDepth = overlapX;
        } else {
            if (r1pos.y > r2pos.y) { // if Y axis collision:
                pointA = Vector2(r1pos.x, r1Bot);
                pointB = Vector2(r2pos.x, r2Top);
            } else {
                pointA = Vector2(r1pos.x, r1Top);
                pointB = Vector2(r2pos.x, r2Bot);
            }
            penDepth = overlapY;
        }
        addClPair(r1, pointA, r2, pointB, penDepth);
    }
}

// interfaces:
// adds collisions pairs to the m_collisionPair member
void CollisionDetection::addClPair(Object* obj1, Vector2 pointA, Object* obj2, Vector2 pointB, float depth) {
    std::unique_ptr<CollisionPair> collisionPair = std::make_unique<CollisionPair>(obj1, pointA, obj2, pointB, depth);
    m_collisionPairs.push_back(std::move(collisionPair));
}

// deletes a pair from m_collisionPair member
void CollisionDetection::deleteClPair(CollisionPair* pair) {
    if (!pair) return;
    auto itr = std::find_if(
        m_collisionPairs.begin(), m_collisionPairs.end(),
        [pair](const std::unique_ptr<CollisionPair>& ptr) { return ptr.get() == pair; });
    if (itr == m_collisionPairs.end()) return;
    m_collisionPairs.erase(itr);
}

/**@return a constant reference to m_collisionPairs*/
const std::vector<std::unique_ptr<CollisionPair>>& CollisionDetection::getClPairs() const { return m_collisionPairs; }
