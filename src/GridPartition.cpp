#include "headers/GridPartition.h"

void GridPartition::updateCellDimensions(std::vector<Object*>& objects){
    //used to update maxH and maxW 
    for(auto* obj : objects){
        Vector2 heighWidth = obj->getDimensions();
        if(heighWidth.x > cellWidth) cellWidth = heighWidth.x;
        if(heighWidth.y > cellHeight) cellHeight = heighWidth.y;
    }
}

//TODO: NEED FIX
void GridPartition::updateCells(PhysicsWorld world){
    // m_cellObjects[col][row]
    for(auto& col : m_cellObjects) {
        col.clear();
    }

    //loops over all objects in world and adds them to a cell
    for(Object* obj : world.getObjects()){
        Vector2 objPos = obj->transform.position;
        int col = static_cast<int>(objPos.x / cellWidth);
        int row = static_cast<int>(objPos.y / cellHeight);

        //checks for out of bound
        if (col >= 0 && col < colnum && row >= 0 && row < rownum) {
            m_cellObjects[col][row] = obj;
        }
    }
}

int GridPartition::getRowCount(){
    return rownum;
}

int GridPartition::getColCount(){
    return colnum;
}

//broken
Object *GridPartition::getObjectInCell(int col, int row){
    return m_cellObjects[col][row];
}
