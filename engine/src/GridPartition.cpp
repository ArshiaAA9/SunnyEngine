#include "headers/GridPartition.h"

#include <iostream>

#include "headers/Physics.h"
#include "headers/Types.h"

namespace SE {
// FIX: BUGGY GRID TOP STATIC BOUNDRY OBJECT NOT WORKING WHEN TOO FAR

// use it to update biggest grid cell size
// FIX: CHANGE THIS FUNCTION SO IT DOESNT NEED TO BE USED AT START
// CHECK IF THIS IS USED BEFORE. IF NOT THROW ERORR
void GridPartition::updateCellDimensions() {
    // used to update maxH and maxW
    auto& allObjects = m_world.handler.getObjects();
    for (auto& obj : allObjects) {
        Dimensions dimensions = obj->getDimensions();
        ObjectType objType = obj->getType();
        if (objType == RECT) {
            if (dimensions.w > cellWidth) cellWidth = dimensions.w;
            if (dimensions.h > cellHeight) cellHeight = dimensions.h;
        } else if (objType == CIRCLE) {
            float radius = dimensions.r;
            if (radius > cellWidth) cellWidth = radius;
            if (radius > cellHeight) cellHeight = radius;
        }
    }
    rownum = gridHeight / cellHeight;
    colnum = gridWidth / cellWidth;
}

// main grid method
void GridPartition::updateCells() {
    // m_cellObjects[col][row][objects]
    deleteAllObject();

    // std::cout << "cellWidth: " << cellWidth << " cellHeight: " << cellHeight << '\n';
    // loops over all object&s in world and adds them to a cell
    for (auto& obj : m_world.handler.getObjects()) {
        Vector2 objPos = obj->transform.position;
        int col = static_cast<int>(objPos.x / cellWidth);
        int row = static_cast<int>(objPos.y / cellHeight);
        // std::cout << "col: " << col << " colnum: " << colnum << "\nrow: " << row
        //           << " rownum:" << rownum << '\n';
        // checks for out of bound
        if (col >= 0 && col <= colnum && row >= 0 && row <= rownum) {
            m_cellObjects[col][row].push_back(obj);
            // std::cout << "adding object\n";
        }
    }
}

int GridPartition::getRowCount() const { return rownum; }

int GridPartition::getColCount() const { return colnum; }

void GridPartition::deleteAllObject() {
    // m_cellObjects[col][row][objects]
    for (auto& col : m_cellObjects) {
        for (auto& row : col) {
            row.clear(); // Clear all objects vectors
        }
    }
}

void GridPartition::logAllObjects() {
    int count = 0;
    // m_cellObjects[col][row][objects]
    for (auto& col : m_cellObjects) {
        for (auto& row : col) {
            for (auto& obj : row) {
                obj->printProperties();
                count++;
            }
        }
    }
    std::cout << " Count: " << count << '\n';
}

const std::vector<ObjectPtr>& GridPartition::getObjectInCell(int col, int row) const { return m_cellObjects[col][row]; }

// private methods:
} // namespace SE
