#pragma once

#include <memory>
#include <vector>

#include "Objects.h"

class PhysicsWorld;
struct Object;

class GridPartition {
public:
    GridPartition(float gridHeight, float gridWidth, PhysicsWorld& world)
        : gridHeight(gridHeight)
        , gridWidth(gridWidth)
        , m_world(world) {
        rownum = gridHeight / cellHeight;
        colnum = gridWidth / cellWidth;

        // initialize the vector
        m_cellObjects.resize(static_cast<size_t>(colnum));
        for (auto& col : m_cellObjects) {
            col.resize(static_cast<size_t>(colnum));
        }
    }

    void updateCellDimensions();

    void updateCells();

    int getRowCount() const;

    int getColCount() const;

    const std::vector<std::unique_ptr<Object>>& getObjectInCell(int col, int row) const;

private:
    PhysicsWorld& m_world;

    float colnum, rownum;
    float gridHeight, gridWidth;
    float cellWidth = 1.0f;
    float cellHeight = 1.0f;

    // sucks but makes most sense first vector represent col 2nd row 3rd the cell with objects inside of it
    std::vector<std::vector<std::vector<std::unique_ptr<Object>>>> m_cellObjects;
};
