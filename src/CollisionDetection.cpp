#include "headers/CollisionDetection.h"

void CollisionDetection::checkCollision(GridPartition& grid) {
    int rows = grid.getRowCount();
    int cols = grid.getColCount();

    // Loop through each cell in the grid
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            // Get the list of objects in the current cell
            auto& objectsInCell = grid.getObjectsInCell(col, row);

            // Check collisions between objects in the same cell
            for (size_t i = 0; i < objectsInCell.size(); ++i) {
                for (size_t j = i + 1; j < objectsInCell.size(); ++j) {
                    checkCollisionByType(objectsInCell[i], objectsInCell[j]);
                }
            }

            // Check collisions with objects in adjacent cells
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue; // Skip the current cell

                    int adjacentCol = col + dx;
                    int adjacentRow = row + dy;

                    // Ensure the adjacent cell is within the grid bounds
                    if (adjacentCol >= 0 && adjacentCol < cols && adjacentRow >= 0 && adjacentRow < rows) {
                        auto& adjacentObjects = grid.getObjectsInCell(adjacentCol, adjacentRow);

                        // Check collisions between objects in the current cell and adjacent cell
                        for (auto& obj1 : objectsInCell) {
                            for (auto& obj2 : adjacentObjects) {
                                checkCollisionByType(*obj1, *obj2);
                            }
                        }
                    }
                }
            }
        }
    }
}

//used inside checkCollision function
void CollisionDetection::checkCollisionByType(Object* obj1, Object* obj2) {
    if (obj1->type == Object::RECT && obj2->type == Object::RECT) { // Rect-Rect
        clRectRect(static_cast<RectObject&>(obj1), static_cast<RectObject&>(obj2));
    } else if (obj1->type == Object::CIRCLE && obj2->type == Object::CIRCLE) { // Circle-Circle
        clCircleCircle(static_cast<CircleObject&>(obj1), static_cast<CircleObject&>(obj2));
    } else if ((obj1->type == Object::RECT && obj2->type == Object::CIRCLE) || 
               (obj1->type == Object::CIRCLE && obj2->type == Object::RECT)) { // Rect-Circle or Circle-Rect
        // Ensure the first object is always the circle
        if (obj1->type == Object::CIRCLE) {
            clCircleRect(static_cast<CircleObject&>(obj1), static_cast<RectObject&>(obj2));
        } else {
            clCircleRect(static_cast<CircleObject&>(obj2), static_cast<RectObject&>(obj1));
        }
    }
}

void CollisionDetection::clCircleCircle(CircleObject& c1, CircleObject& c2){
    float squaredDistance = c1.transform.position.squaredLengthOf2Pos(c2.transform.position);

    if(squaredDistance <= (c1.radius + c2.radius) * (c1.radius + c2.radius)){
        float depth = (c1.radius - c2.radius) - std::sqrt(squaredDistance);  
        
        createCollisionPair(&c1, &c2, depth);
    }
}

// Circle vs. Rectangle Collision Detection
void CollisionDetection::clCircleRect(CircleObject& c, RectObject& rect) {
    Vector2 cPos = c.transform.position;
    Vector2 rectPos = rect.transform.position;

    float rectLeft = rectPos.x - rect.width / 2;
    float rectRight = rectPos.x + rect.width / 2;
    float rectTop = rectPos.y + rect.height / 2;
    float rectBottom = rectPos.y - rect.height / 2;

    // Closest point on rectangle to circle center
    float closestX = std::max(rectLeft, std::min(cPos.x, rectRight));
    float closestY = std::max(rectBottom, std::min(cPos.y, rectTop));

    // Compute squared distance between closest point and circle center
    float squaredDist = (cPos.x - closestX) * (cPos.x - closestX) + 
                        (cPos.y - closestY) * (cPos.y - closestY);

    if (squaredDist <= c.radius * c.radius) {
        float depth = c.radius - std::sqrt(squaredDist);
        createCollisionPair(&c, &rect, depth);
    }
}

bool CollisionDetection::aabb(RectObject& r1, RectObject& r2){
    Vector2 r1Pos = r1.transform.position;
    Vector2 r2Pos = r2.transform.position;

    float r1Left = r1Pos.x - r1.width / 2;
    float r1Right = r1Pos.x + r1.width / 2;
    float r1Top = r1Pos.y + r1.height / 2;
    float r1Bot = r1Pos.y - r1.height / 2;

    float r2Left =  r2Pos.x - r2.width / 2;
    float r2Right = r2Pos.x + r2.width / 2;
    float r2Top = r2Pos.y + r2.height / 2;
    float r2Bot = r2Pos.y - r2.height / 2;


    return (r1Left  <= r2Right
    && r1Right >= r2Left
    && r1Bot <= r2Top
    && r1Top >= r2Bot);
}

void CollisionDetection::clRectRect(RectObject& r1, RectObject& r2){
    if (aabb(r1, r2)) {
        float r1Left = r1.transform.position.x - r1.width / 2;
        float r1Right = r1.transform.position.x + r1.width / 2;
        float r1Top = r1.transform.position.y + r1.height / 2;
        float r1Bot = r1.transform.position.y - r1.height / 2;

        float r2Left = r2.transform.position.x - r2.width / 2;
        float r2Right = r2.transform.position.x + r2.width / 2;
        float r2Top = r2.transform.position.y + r2.height / 2;
        float r2Bot = r2.transform.position.y - r2.height / 2;

        // Calculate overlap on both axes
        float overlapX = std::min(r1Right - r2Left, r2Right - r1Left);
        float overlapY = std::min(r1Top - r2Bot, r2Top - r1Bot);

        // Find the smallest overlap (collision depth)
        float penetrationDepth = std::min(overlapX, overlapY);

        createCollisionPair(&r1, &r2, penetrationDepth);
    }

}

void CollisionDetection::createCollisionPair(Object* obj1, Object* obj2, float depth){
    CollisionPair* collision = new CollisionPair(obj1, obj2, depth);
    m_collisionPairs.push_back(collision);
}

