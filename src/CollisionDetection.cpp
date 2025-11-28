#include "CollisionDetection.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "GridPartition.h"
#include "Objects.h"
#include "Types.h"
#include "Vector2.h"

// TODO: ADD A WAY FOR USER TO CHECK IF TWO SPECIFIC OBJECT COLLIDE WITH EATCH OTHER

namespace SE {

/**@brief Performs collision detection using a spatial grid partitioning system.
 * @brief Iterates through all grid cells, checks collisions between objects within the same cell,
 * @brief and between objects in neighboring cells to handle boundary/cross-cell collisions.*/
void CollisionDetection::checkCollisions() {
    // Get grid dimensions
    int rowCount = grid.getRowCount();
    int colCount = grid.getColCount();

    // Iterate through all cells in the grid
    for (int col = 0; col < colCount; col++) {
        for (int row = 0; row < rowCount; row++) {
            // Get reference to objects in current cell
            auto& objectsInCell = grid.getObjectInCell(col, row);

            // Skip empty cells to optimize processing
            if (objectsInCell.empty()) continue;

            // Check collisions between all unique pairs in current cell
            // Uses i/j nested loops to avoid duplicate checks (A-B vs B-A)
            for (size_t i = 0; i < objectsInCell.size(); i++) {
                for (size_t j = i + 1; j < objectsInCell.size(); j++) {
                    ObjectPtr obj1 = objectsInCell[i];
                    ObjectPtr obj2 = objectsInCell[j];
                    // std::cout << " Object1&: " << obj1 << " Object2&: " << obj2 << '\n';
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
                        auto& pNeighborObjectsInCell = grid.getObjectInCell(neighborCol, neighborRow);

                        // Check all object pairs between current and neighbor cell
                        for (auto& obj1 : objectsInCell) {
                            for (auto& obj2 : pNeighborObjectsInCell) {
                                checkCollisionByType(obj1, obj2);
                            }
                        }
                    }
                }
            }
        }
    }
}

// used inside checkCollision function
void CollisionDetection::checkCollisionByType(ObjectPtr obj1, ObjectPtr obj2) {
    if (obj1->isStatic() && obj2->isStatic()) {
        return;
    } else if (obj1->getType() == RECT && obj2->getType() == RECT) { // Rect-Rect
        if (obj1->transform.getAngle() == 0 && obj2->transform.getAngle() == 0) {
            aabb(obj1, obj2);
        } else {
            sat(obj1, obj2);
        }
    } else if (obj1->getType() == CIRCLE && obj2->getType() == CIRCLE) { // Circle-Circle
        clCircleCircle(obj1, obj2);
    } else if (
        (obj1->getType() == RECT && obj2->getType() == CIRCLE) ||
        (obj1->getType() == CIRCLE && obj2->getType() == RECT)) { // Rect-Circle or Circle-Rect
        // Ensure the first object is always the circle
        if (obj1->getType() == CIRCLE) {
            clCircleRect(obj1, obj2);

        } else {
            clCircleRect(obj2, obj1);
        }
    }
}

void CollisionDetection::clCircleCircle(ObjectPtr c1, ObjectPtr c2) {
    float distance = c1->transform.position.lengthOf2Pos(c2->transform.position);
    float c1r = c1->getDimensions().r;
    float c2r = c2->getDimensions().r;
    // a collision is found
    if (distance <= (c1r + c2r)) {
        float depth = (c1r + c2r) - distance;
        // calculating pointA pointB:
        Vector2 direction = c1->transform.position - c2->transform.position;
        direction.normalize();

        Vector2 pointA = c1->transform.position - direction * c1r;
        Vector2 pointB = c2->transform.position - direction * c2r;
        addClPair(c1, pointA, c2, pointB, depth, direction);
    }
}

// Circle vs. Rectangle Collision Detection
void CollisionDetection::clCircleRect(ObjectPtr c, ObjectPtr rect) {
    Vector2 cPos = c->transform.position;
    Vector2 rectPos = rect->transform.position;
    float r = c->getDimensions().r;
    float halfWidth = rect->getDimensions().w / 2.0f;
    float halfHeight = rect->getDimensions().h / 2.0f;

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
        addClPair(c, pointA, rect, pointB, penDepth, direction);
    }
}

void CollisionDetection::sat(ObjectPtr r1, ObjectPtr r2) {
    // std::cout << "sat\n";
    auto& verticesA = r1->transform.transformedVertices;
    auto& verticesB = r2->transform.transformedVertices;
    float minOverlap = INFINITY; // used to find penDepth
    Vector2 collisionNormal;

    // first polygon
    for (size_t i = 0; i < verticesA.size(); i++) {
        Vector2 vertex1 = verticesA[i];
        Vector2 vertex2 = verticesA[(i + 1) % verticesA.size()]; // use modulu operator to avoid out of bound

        Vector2 edge = vertex2 - vertex1;
        if (edge.squaredMagnitude() < 1e-8) continue;
        Vector2 axis = Vector2(edge.y, -edge.x);
        axis.normalize();

        Vector2 minMaxA = satProject(verticesA, axis);
        Vector2 minMaxB = satProject(verticesB, axis);
        float overlap = std::min(minMaxA.y, minMaxB.y) - std::max(minMaxA.x, minMaxB.x);

        if (minMaxA.x >= minMaxB.y || minMaxB.x >= minMaxA.y) return;
        if (overlap < minOverlap) {
            minOverlap = overlap;
            collisionNormal = axis;
        }
    }

    // second polygon
    for (size_t i = 0; i < verticesB.size(); i++) {
        Vector2 vertex1 = verticesB[i];
        Vector2 vertex2 = verticesB[(i + 1) % verticesB.size()]; // use modulu operator to avoid out of bound

        Vector2 edge = vertex2 - vertex1;
        Vector2 axis = Vector2(edge.y, -edge.x);
        axis.normalize();

        Vector2 minMaxA = satProject(verticesA, axis);
        Vector2 minMaxB = satProject(verticesB, axis);
        float overlap = std::min(minMaxA.y, minMaxB.y) - std::max(minMaxA.x, minMaxB.x);

        if (minMaxA.x >= minMaxB.y || minMaxB.x >= minMaxA.y) return;
        if (overlap < minOverlap) {
            minOverlap = overlap;
            collisionNormal = axis;
        }
    }
    Vector2 dir = r1->transform.position - r2->transform.position;
    if (dir.dotProduct(collisionNormal) < 0) {
        collisionNormal.invert(); // Flip direction if needed
    }

    Vector2 pointA;
    float maxProjA = -INFINITY;
    for (auto& vertex : verticesA) {
        float proj = vertex.dotProduct(collisionNormal);
        if (proj > maxProjA) {
            maxProjA = proj;
            pointA = vertex;
        }
    }

    Vector2 pointB;
    float minProjB = INFINITY;
    for (auto& vertex : verticesB) {
        float proj = vertex.dotProduct(collisionNormal);
        if (proj < minProjB) {
            minProjB = proj;
            pointB = vertex;
        }
    }

    float penDepth = minOverlap;
    addClPair(r1, pointA, r2, pointB, penDepth, collisionNormal);
}

Vector2 CollisionDetection::satProject(std::vector<Vector2>& vertices, Vector2 axis) {
    float min = INFINITY;
    float max = -INFINITY;

    for (size_t i = 0; i < vertices.size(); i++) {
        Vector2 vertex = vertices[i];
        float projection = vertex.dotProduct(axis);

        min = std::min(min, projection);
        max = std::max(max, projection);
    }
    return Vector2(min, max);
}

// FIX: DOESNT WORK WITH ROTATED OBJECTS CAUSE OF ROTATED WIDTH HEIGHT
void CollisionDetection::aabb(ObjectPtr r1, ObjectPtr r2) {
    // std::cout << "aabb\n";
    Vector2 r1Pos = r1->transform.position;
    Vector2 r2Pos = r2->transform.position;

    float halfWidth1 = r1->getDimensions().w / 2.0f;
    float halfHeight1 = r1->getDimensions().h / 2.0f;

    float halfWidth2 = r2->getDimensions().w / 2.0f;
    float halfHeight2 = r2->getDimensions().h / 2.0f;

    float r1Left = r1Pos.x - halfWidth1;
    float r1Right = r1Pos.x + halfWidth1;
    float r1Top = r1Pos.y + halfHeight1;
    float r1Bot = r1Pos.y - halfHeight1;

    float r2Left = r2Pos.x - halfWidth2;
    float r2Right = r2Pos.x + halfWidth2;
    float r2Top = r2Pos.y + halfHeight2;
    float r2Bot = r2Pos.y - halfHeight2;

    if (r1Left <= r2Right && r1Right >= r2Left && r1Bot <= r2Top && r1Top >= r2Bot) {
        // Calculate overlap on both axes
        float overlapX = std::min(r1Right, r2Right) - std::max(r1Left, r2Left);
        float overlapY = std::min(r1Top, r2Top) - std::max(r1Bot, r2Bot);
        Vector2 normal;

        Vector2 pointA, pointB;
        float penDepth;
        // the collision is primarily on smaller overlap
        if (overlapX < overlapY) { // if X axis collision:
            if (r1Pos.x > r2Pos.x) {
                normal = Vector2(1, 0);
                pointA = Vector2(r1Left, r1Pos.y);
                pointB = Vector2(r2Right, r2Pos.y);
            } else {
                normal = Vector2(-1, 0);
                pointA = Vector2(r1Right, r1Pos.y);
                pointB = Vector2(r2Left, r2Pos.y);
            }
            penDepth = overlapX;
        } else {
            if (r1Pos.y > r2Pos.y) { // if Y axis collision:
                pointA = Vector2(r1Pos.x, r1Bot);
                pointB = Vector2(r2Pos.x, r2Top);
                normal = Vector2(0, 1);
            } else {
                normal = Vector2(0, -1);
                pointA = Vector2(r1Pos.x, r1Top);
                pointB = Vector2(r2Pos.x, r2Bot);
            }
            penDepth = overlapY;
        }
        addClPair(r1, pointA, r2, pointB, penDepth, normal);
    }
}

// interfaces:
// adds collisions pairs to the m_collisionPair member
void CollisionDetection::addClPair(
    ObjectPtr obj1, Vector2 pointA, ObjectPtr obj2, Vector2 pointB, float depth, Vector2 normal) {
    std::unique_ptr<CollisionPair> collisionPair =
        std::make_unique<CollisionPair>(obj1, pointA, obj2, pointB, depth, normal);
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

} // namespace SE
