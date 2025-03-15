#include "headers/GridPartition.h"

#include <iostream>

#include "headers/Objects.h"
#include "headers/Physics.h"

// use it to update biggest grid cell size
void GridPartition::updateCellDimensions() {
    // used to update maxH and maxW
    auto& allObjects = m_world.Handler.getObjects();
    for (auto& obj : allObjects) {
        // x = width y = height
        Vector2 heighWidth = obj->getDimensions();
        if (obj->type == RECT) {

            if (heighWidth.x > cellWidth) cellWidth = heighWidth.x;
            if (heighWidth.y > cellHeight) cellHeight = heighWidth.y;
        } else if (obj->type == CIRCLE) {
            // y = diameter
            float radius = heighWidth.y;
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
    for (auto& col : m_cellObjects) {
        for (auto& row : col) {
            row.clear(); // Clear all objects vectors
        }
    }

    // loops over all object&s in world and adds them to a cell
    for (auto& obj : m_world.Handler.getObjects()) {
        Vector2 objPos = obj->transform.position;
        int col = static_cast<int>(objPos.x / cellWidth);
        int row = static_cast<int>(objPos.y / cellHeight);

        // checks for out of bound
        if (col >= 0 && col < colnum && row >= 0 && row < rownum) {
            // std::cout << "col " << col << " row: " << row << '\n';
            // dont use move cause it stores raw pointer
            m_cellObjects[col][row].push_back(obj.get());
            // logAllObjects();
        }
    }
}

int GridPartition::getRowCount() const { return rownum; }

int GridPartition::getColCount() const { return colnum; }

// private methods:
void GridPartition::logAllObjects() {
    int count = 0;
    // m_cellObjects[col][row][objects]
    for (auto& col : m_cellObjects) {
        for (auto& row : col) {
            for (auto& obj : row) {
                count++;
                obj->printProperties();
            }
        }
    }
    std::cout << " Count: " << count << '\n';
}

const std::vector<Object*>& GridPartition::getObjectInCell(int col, int row) const { return m_cellObjects[col][row]; }
