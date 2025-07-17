#include "headers/ObjectHandler.h"

#include <algorithm>
#include <memory>

#include "headers/Types.h"

namespace SE {

void ObjectHandler::addObject(ObjectPtr object) {
    // ObjectPtr is a shared pointer
    m_objects.push_back(std::move(object));
}

void ObjectHandler::deleteObject(ObjectPtr object) {
    if (!object) return;
    auto itr = std::find(m_objects.begin(), m_objects.end(), object);
    if (itr == m_objects.end()) return;
    m_objects.erase(itr);
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
