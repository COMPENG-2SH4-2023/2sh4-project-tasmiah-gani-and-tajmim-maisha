#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];  // 256 elements on the heap
    listSize = 0;                       // no valid element in the list upon startup
    arrayCapacity = ARRAY_MAX_CAP;      // array capacity should be max
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; // call the destructors of all instances in the array
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // need error check-what if list size is at capacity?
    //check if listSize is equal to arrayCapacity. If yes, at capacity don't insert.

    if(listSize == arrayCapacity) {
        return;
    }

    for(int i = listSize; i > 0; i--) {
        aList[i].setObjPos(aList[i-1]); // shuffle all elements towards the tail
    }
    aList[0].setObjPos(thisPos);

    listSize++;

}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity) {
        return;
    }

    aList[listSize++].setObjPos(thisPos);
}

void objPosArrayList::removeHead()
{
    if (listSize == 0) {
        return;
    }

    for (int i = 0; i < listSize - 1; i++) {
        aList[i].setObjPos(aList[i + 1]);
    }

    listSize--;

}

void objPosArrayList::removeTail()
{
    if (listSize == 0) {
        return;
    }

    listSize--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if(listSize == 0) {
        return;
    }
    
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if(listSize == 0) {
        return;
    }

    returnPos.setObjPos(aList[listSize - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if(listSize == 0 || index < 0 || index > listSize + 1) {
        return;
    }

    returnPos.setObjPos(aList[index]);

}