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
    GridPartition m_grid;

    Vector2 m_gravity = Vector2(0, -9.81);

public:
    CollisionDetection cD;
    ObjectHandler Handler;

    /**
     *@param gridHeight simulations height
     *@param gridWidth simulations width
     *@return
     * */
    PhysicsWorld(float gridHeight, float gridWidth) : m_grid(gridHeight, gridWidth, this), cD(&m_grid), Handler(this) {}

    void dynamicsUpdate(float dt);
    void step(float dt);

    void setGravity(Vector2 gravity);
};
