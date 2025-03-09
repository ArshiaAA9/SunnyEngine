#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include "CollisionDetection.h"
#include "CollisionPair.h"
#include "GridPartition.h"
#include "ObjectHandler.h"
#include "Objects.h"
#include "Solver.h"
#include "Vector2.h"

/*
TODO: write interfaces inside all of the member classes specialy collision detection and update the
functions that add pairs to the pair vectors*/
class PhysicsWorld {
private:
    Solver m_solver;
    Vector2 m_gravity = Vector2(0, -9.81);

public:
    CollisionDetection cD; // public cause owns collisionPairs
    ObjectHandler Handler; // public cause handles Objects

    /**
     *@param gridHeight simulations height
     *@param gridWidth simulations width
     *@return
     * */
    PhysicsWorld(float gridHeight, float gridWidth)
        : cD(gridHeight, gridWidth, *this)
        , m_solver(*this)
        , Handler(*this) {}

    void dynamicsUpdate(float dt);
    void step(float dt);

    void setGravity(Vector2 gravity);
};
