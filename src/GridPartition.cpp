#include "headers/GridPartition.h"

#include "headers/Physics.h"

void GridPartition::updateCellDimensions() {
    // used to update maxH and maxW
    auto& allObjects = m_world.Handler.getObjects();
    for (auto& obj : allObjects) {
        Vector2 heighWidth = obj->getDimensions();
        if (heighWidth.x > cellWidth) cellWidth = heighWidth.x;
        if (heighWidth.y > cellHeight) cellHeight = heighWidth.y;
    }
    rownum = gridHeight / cellHeight;
    colnum = gridWidth / cellWidth;
}

void GridPartition::updateCells() {
    // m_cellObjects[col][row][objects]
    for (auto& col : m_cellObjects) {
        for (auto& row : col) {
            row.clear(); // Clear the objects in the current row
        }
    }

    // loops over all object&s in world and adds them to a cell
    for (const auto& obj : m_world.Handler.getObjects()) {
        Vector2 objPos = obj->transform.position;
        int col = static_cast<int>(objPos.x / cellWidth);
        int row = static_cast<int>(objPos.y / cellHeight);

        // checks for out of bound
        if (col >= 0 && col < colnum && row >= 0 && row < rownum) {
            m_cellObjects[col][row].push_back(obj);
        }
    }
}

int GridPartition::getRowCount() const { return rownum; }

int GridPartition::getColCount() const { return colnum; }

const std::vector<std::unique_ptr<Object>>& GridPartition::getObjectInCell(int col, int row) const {
    return m_cellObjects[col][row];
}
