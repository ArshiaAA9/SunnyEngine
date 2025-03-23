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

/**@return returns pointer all objects in the world**/
const std::vector<ObjectPtr>& ObjectHandler::getObjects() const { return m_objects; }

/**
 * @brief Creates a rectObject and adds it to the world
 * @brief returning a pointer raw pointer so user can interact with it
 *
 * This function creates a new `RectObject` with the specified position, mass, width, and height.
 * The newly created object is then added to the world managed by the `ObjectHandler`.
 *
 * @param x The x-coordinate of the object's position.
 * @param y The y-coordinate of the object's position.
 * @param mass The mass of the object.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @return A pointer to the newly created `RectObject`.
 *
 */
ObjectPtr ObjectHandler::createRectObj(float x, float y, float mass, float width, float height) {
    // ObjectPtr = std::shared_ptr<Object>
    ObjectPtr rectObject = std::make_shared<RectObject>(x, y, mass, width, height);
    addObject(rectObject);
    return rectObject;
}

/**
 * @brief Creates a circular object and adds it to the world.
 *
 * This function creates a new `CircleObject` with the specified position, mass, and radius.
 * The newly created object is then added to the world managed by the `ObjectHandler`.
 *
 * @param x The x-coordinate of the object's position.
 * @param y The y-coordinate of the object's position.
 * @param mass The mass of the object.
 * @param radius The radius of the circle.
 * @return A pointer to the newly created `CircleObject`.
 *
 */
ObjectPtr ObjectHandler::createCircleObj(float x, float y, float mass, float radius) {
    std::shared_ptr<Object> circleObject = std::make_shared<CircleObject>(x, y, mass, radius);
    addObject(circleObject);
    return circleObject;
}
} // namespace SE
