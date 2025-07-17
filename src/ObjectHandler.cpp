#include "ObjectHandler.h"

#include <algorithm>
#include <iostream>
#include <memory>

#include "Types.h"

namespace SE {

void ObjectHandler::addObject(ObjectPtr object) {
    // ObjectPtr is a shared pointer
    m_objects.push_back(std::move(object));
}

bool ObjectHandler::deleteObject(ObjectPtr object) {
    if (!object) {
        std::cerr << "[WARN] Attempted to delete null object\n";
        return false;
    }
    auto itr = std::find(m_objects.begin(), m_objects.end(), object);
    if (itr == m_objects.end()) {
        std::cerr << "[INFO] Object not found";
        return false;
    }
    m_objects.erase(itr);
    return true;
}

const std::vector<ObjectPtr>& ObjectHandler::getObjects() const { return m_objects; }

ObjectPtr ObjectHandler::createRectObj(float x, float y, float mass, float width, float height) {
    // ObjectPtr = std::shared_ptr<Object>
    ObjectPtr rectObject = std::make_shared<RectObject>(x, y, mass, width, height);
    addObject(rectObject);
    return rectObject;
}

ObjectPtr ObjectHandler::createStaticRect(float x, float y, float width, float height) {
    // ObjectPtr = std::shared_ptr<Object>
    ObjectPtr staticRectObject = std::make_shared<RectObject>(x, y, width, height);
    addObject(staticRectObject);
    return staticRectObject;
}

ObjectPtr ObjectHandler::createCircleObj(float x, float y, float mass, float radius) {
    ObjectPtr circleObject = std::make_shared<CircleObject>(x, y, mass, radius);
    addObject(circleObject);
    return circleObject;
}

ObjectPtr ObjectHandler::createStaticCircle(float x, float y, float radius) {
    ObjectPtr staticCircleObject = std::make_shared<CircleObject>(x, y, radius);
    addObject(staticCircleObject);
    return staticCircleObject;
}
} // namespace SE
