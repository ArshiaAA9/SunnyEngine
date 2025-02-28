#pragma once

#include <vector>
#include "Objects.h"
#include "Physics.h"

class PhysicsWorld;
struct Object;

class GridPartition {
public:

    void updateCellDimensions(std::vector<Object*>& objects);

    void updateCells(PhysicsWorld world);

    int getRowCount();

    int getColCount();

    Object* getObjectsInCell(int col, int row);


private:
    float colnum, rownum;
    float gridHeight, gridWidth;
    float cellWidth = 1.0f;
    float cellHeight = 1.0f;
    
    std::vector<std::vector<Object*>> m_cellObjects;

    GridPartition(float gridHeight, float gridWidth) : gridHeight(gridHeight), gridWidth(gridWidth) {
        rownum = gridHeight / cellHeight;
        colnum = gridWidth / cellWidth;

        //initialize the vector
        m_cellObjects.resize(static_cast<size_t>(colnum));
        for (auto& row : m_cellObjects) {
            row.resize(static_cast<size_t>(rownum));
        }
    }

    friend class Init;
};