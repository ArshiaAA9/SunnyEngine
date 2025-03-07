#include "headers/ObjectHandler.h"

#include <algorithm>
void ObjectHandler::addObject(Object* object) { m_objects.push_back(object); }

void ObjectHandler::deleteObject(Object* object) {
    // if nullptr
    if (!object) return;
    auto itr = std::find(m_objects.begin(), m_objects.end(), object);
    if (itr == m_objects.end()) return;
    m_objects.erase(itr);
    delete object;
    object = nullptr;
}

/**@return returns pointer all objects in the world**/
std::vector<Object*>* ObjectHandler::getObjects() { return &m_objects; }

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
 * @return A pointer to the newly created `RectObject`.
 *
 * @note The caller is responsible for managing the lifetime of the returned object.
 *       Ensure proper cleanup to avoid memory leaks.
 */
Object* ObjectHandler::createRectObjptr(float x, float y, float mass, float width, float height) {
    Object* rectObject = new RectObject(x, y, mass, width, height);
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
 * @note The caller is responsible for managing the lifetime of the returned object.
 *       Ensure proper cleanup to avoid memory leaks.
 */
Object* ObjectHandler::createCircleObjptr(float x, float y, float mass, float radius) {
    Object* circleObject = new CircleObject(x, y, mass, radius);
    addObject(circleObject);
    return circleObject;
}
