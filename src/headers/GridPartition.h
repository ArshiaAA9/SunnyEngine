#pragma once

#include <vector>
#include "Objects.h"
#include "Physics.h"

//uniform grid partitioning 


// every grid will contain elements inside of it
class GridPartition {
private:
    float colnum, rownum;
    float gridHeight, gridWidth;
    float cellWidth = 1.0f, cellHeight = 1.0f;
    
    std::vector<std::vector<Object*>> m_cellObjects;
public:

    GridPartition(float gridHeight, float gridWidth) : gridHeight(gridHeight), gridWidth(gridWidth) {
        rownum = gridHeight / cellHeight;
        colnum = gridWidth / cellWidth;

        //initialize the vector
        m_cellObjects.resize(static_cast<size_t>(colnum));
        for (auto& row : m_cellObjects) {
            row.resize(static_cast<size_t>(rownum));
        }
    }

    void setGridHeightWidth(float height, float width);

    void updateCellDimensions(std::vector<Object*>& objects);

    void updateCells(PhysicsWorld world);
}