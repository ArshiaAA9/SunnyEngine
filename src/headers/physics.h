#pragma once

#include <iostream>
#include "vector2.h"
#include "objects.h"

const float GRAVITY = 9.81;

void updateObject(Object& obj, float deltaTime);

void applyForce(Object& obj, Vector2 force);

void applyGravity(Object& obj);



