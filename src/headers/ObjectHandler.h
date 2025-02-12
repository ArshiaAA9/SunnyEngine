#include "objects.h"
#include "vector2.h"

class ObjectHandler {
private:
    ObjectHandler(PhysicsWorld& world) : world(world) {}

    PhysicsWorld& world;

    friend class init;
public:

    // Factory method to create a rectangle
    Object* rectCreate(float x, float y, float mass, float width, float height) {
        Object* object = new rectObject(x, y, mass, width, height);
        world.addObject(object);
        return object;
    }

};