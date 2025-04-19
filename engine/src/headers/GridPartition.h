#pragma once

#include <memory>
#include <vector>

#include "Objects.h"
#include "Types.h"

namespace SE {
class PhysicsWorld;
struct Object;

class GridPartition {
public:
    GridPartition(int gridHeight, int gridWidth, PhysicsWorld& world)
        : gridHeight(gridHeight)
        , gridWidth(gridWidth)
        , m_world(world) {
        rownum = gridHeight / cellHeight;
        colnum = gridWidth / cellWidth;
        // initialize the vector
        m_cellObjects.resize(static_cast<size_t>(colnum));
        for (auto& col : m_cellObjects) {
            col.resize(static_cast<size_t>(rownum));
        }
    }

    void updateCellDimensions();

    void updateCells();

    int getRowCount() const;

    int getColCount() const;

    void deleteAllObject();

    void logAllObjects();

    // NOTE: check for dangling pointer before use also run it first thing in frame
    const std::vector<ObjectPtr>& getObjectInCell(int col, int row) const;

private:
    PhysicsWorld& m_world;

    int colnum, rownum;
    float gridHeight, gridWidth;
    float cellWidth = 1.0f;
    float cellHeight = 1.0f;

    // sucks but makes most sense first vector represent col 2nd row 3rd the cell with objects
    // inside of it
    std::vector<std::vector<std::vector<ObjectPtr>>> m_cellObjects;
};
} // namespace SE
