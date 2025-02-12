#include "objects.h"
#include "vector2.h"

class ObjectHandling {
private:
    Object* obj;

    ObjectHandling(Object* obj) : obj(obj) {}
public:

    ~ObjectHandling() {
        delete obj;  // Avoid memory leaks by deleting the object when done
    }


    // Factory method to create a rectangle
    static ObjectHandling rectCreate(float x, float y, float mass, float width, float height) {
        return ObjectHandling(new rectObject(x, y, mass, width, height));
    }

    // Factory method to create a circle
    static ObjectHandling circleCreate(float x, float y, float mass, float radius) {
        return ObjectHandling(new circleObject(x, y, mass, radius));
    }

};