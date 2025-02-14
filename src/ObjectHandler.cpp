#include "headers/ObjectHandler.h"

ObjectHandler::rectCreate(float x, float y, float mass, float width, float height) {
    RectObject* rectObject = new RectObject(x, y, mass, width, height);
    world.addObject(RectObject);
    return rectObject;
    
}

ObjectHandler::circleCreate(float x, float y, float mass, float radius){
    CircleObject* circleObject = new CircleObject(x, y, mass, radius);
    world.addObject(circleObject) 
    return circleObject;
}
