#include "GridPartition.h"

void GridPartition::setGridHeightWidth(float height, float width){
    gridHeight = height; gridWidth = width;
}

void GridPartition::updateCellDimensions(std::vector<Object*>& objects){
    //used to update maxH and maxW 
    for(auto* obj : objects){
        Vector2 heighWidth = obj->getHeightWidth();
        if(heighWidth.x > cellWidth) cellWidth = heighWidth.x;
        if(heighWidth.y > cellHeight) cellHeight = heighWidth.y;
    }
}

void GridPartition::updateCells(PhysicsWorld world){
    // Clear previous cell assignments
    for(auto& row : cellObject) {
        for(auto& cell : row) {
            cell.clear();
        }
    }

    //loops over all objects in world and adds them to a cell
    for(Object* obj : world.getObjects){
        Vector2 objPos = obj->transform.position;
        int col = static_cast<int>(objPos.x / cellWidth);
        int row = static_cast<int>(objPos.y / cellHeight);

        //checks for out of bound
        if (col >= 0 && col < colnum && row >= 0 && row < rownum) {
            m_cellObjects[col][row].push_back(obj);
        }
    }
}
