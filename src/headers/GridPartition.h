#pragma once

#include <vector>

#include "Objects.h"

class PhysicsWorld;
struct Object;

class GridPartition {
public:
    GridPartition(float gridHeight, float gridWidth, PhysicsWorld* world)
        : gridHeight(gridHeight), gridWidth(gridWidth), m_world(world) {
        rownum = gridHeight / cellHeight;
        colnum = gridWidth / cellWidth;

        // initialize the vector
        m_cellObjects.resize(static_cast<size_t>(colnum));
        for (auto& row : m_cellObjects) {
            row.resize(static_cast<size_t>(rownum));
        }
    }
    void updateCellDimensions(std::vector<Object*>& objects);

    void updateCells();

    int getRowCount();

    int getColCount();

    Object* getObjectInCell(int col, int row);

private:
    PhysicsWorld* m_world;

    float colnum, rownum;
    float gridHeight, gridWidth;
    float cellWidth = 1.0f;
    float cellHeight = 1.0f;

    std::vector<std::vector<Object*>> m_cellObjects;
};
