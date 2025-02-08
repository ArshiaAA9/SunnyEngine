#pragma once

#include <iostream>
#include "vector2.h"
#include "objects.h"

const Vector2 GRAVITY(0, -9.81);

void updateObject(Object& obj, float deltaTime);

void applyForce(Object& obj, Vector2 force);

void applyGravity(Object& obj);



