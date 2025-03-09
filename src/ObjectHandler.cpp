#include "headers/ObjectHandler.h"

#include <algorithm>
#include <memory>

void ObjectHandler::addObject(std::unique_ptr<Object> object) { m_objects.push_back(object); }

void ObjectHandler::deleteObject(Object* object) {
    if (!object) return;
    auto itr = std::find(m_objects.begin(), m_objects.end(), object);
    if (itr == m_objects.end()) return;
    m_objects.erase(itr);
}

/**@return returns pointer all objects in the world**/
const std::vector<std::unique_ptr<Object>>& ObjectHandler::getObjects() const { return m_objects; }

/**
 * @brief Creates a rectangular object and adds it to the world.
 *
 * This function creates a new `RectObject` with the specified position, mass, width, and height.
 * The newly created object is then added to the world managed by the `ObjectHandler`.
 *
 * @param x The x-coordinate of the object's position.
 * @param y The y-coordinate of the object's position.
 * @param mass The mass of the object.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @return A Reference to the newly created `RectObject`.
 *
 */
Object* ObjectHandler::createRectObj(float x, float y, float mass, float width, float height) {
    std::unique_ptr<Object> rectObject = std::make_unique<RectObject>(x, y, mass, width, height);
    Object* ptr = rectObject.get();
    addObject(std::move(rectObject));
    return ptr;
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
 * @note The caller is responsible for managing the lifetime of the returned object.
 *       Ensure proper cleanup to avoid memory leaks.
 */
Object* ObjectHandler::createCircleObj(float x, float y, float mass, float radius) {
    std::unique_ptr<Object> circleObject = std::make_unique<CircleObject>(x, y, mass, radius);
    Object* ptr = circleObject.get();
    addObject(std::move(circleObject));
    return ptr;
}
