#include "headers/CollisionDetection.h"

//ignore this its not complete
void CollisionDetection::checkCollision(GridPartition grid){
    std::vector<std::vector<Object *>>& cells = grid.getCells();
}

void CollisionDetection::clCircleCircle(CircleObject& c1, CircleObject& c2){
    float squaredDistance = c1.transform.position.squaredLengthOf2Pos(c2);

    if(squaredDistance <= (c1.radius + c2.radius) * (c1.radius + c2.radius)){
        c1.collider.hasCollision = true;
        c2.collider.hasCollision = true;
    
    }else{
        c1.collider.hasCollision = false;
        c2.collider.hasCollision = false;
    }
}

void CollisionDetection::clCircleRect(CircleObject& c, RectObject& rect){
    Vector2 cPos = c.transform.position;
    Vector2 rectPos = rect.transform.position;
    
    if(cPos.x + c.radius >= rectPos.x - rect.width / 2 
    && cPos.x - c.radius <= rectPos.x + rect.width / 2
    && cPos.y + c.radius >= rectPos.y - rect.height / 2
    && cPos.y - c.radius <= rectPos.y + rect.height / 2){
        collisionPair* collision = createCollisions(*c, *rect);
        m_collisions.push_back(collision);
    }else{
        c.collider.hasCollision = false;
        rect.collider.hasCollision = false;
    }
}

bool CollisionDetection::AABB(RectObject& r1, RectObject& r2){
    Vector2 r1Pos = r1.transform.position;
    Vector2 r2Pos = r2.transform.position;

    return (r1Pos.x - r1.width / 2 <= r2Pos.x + r2.width / 2
    && r1Pos.x + r1.width / 2 >= r2Pos.x - r2.width / 2
    && r1Pos.y - r1.height / 2 <= r2Pos.y + r2.height / 2
    && r1Pos.y + r1.height / 2 >= r2Pos.y - r2.height / 2);
}

void CollisionDetection::clRectRect(RectObject& r1, RectObject& r2){
    bool hasCollision = AABB(r1, r2)
        r1.collider.hasCollision = hasCollision;
        r2.collider.hasCollision = hasCollision;
}

CollisionPair* CollisionDetection::createCollisions(Object* obj1, Object* obj2){
    collision = new CollisionPair(obj1, obj2);
    return collision;
}