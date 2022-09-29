#include "field.h"


void Field::initField(int currentX, int currentY, int fullX, int fullY)
{
    currentSizeX = currentX;
    currentSizeY = currentY;
    fullSizeX = fullX;
    fullSizeY = fullY;
    fieldMap = new int* [fullSizeX];
    for (int countX = 0; countX < fullSizeX; countX++){
        fieldMap[countX] = new int [fullSizeY];
        for (int countY = 0; countY < fullSizeY; countY++){
            fieldMap[countX][countY] = Field::Free;
        }
    }
}


void Field::drawField()
{
    for(int countX = currentBeginX; countX < currentSizeX; countX++){
        for(int countY = currentBeginY; countY < currentSizeY; countY++){
            drawCell(countX, countY);
        }
    }
}


int Field::getCurrentBeginX()
{
    return currentSizeX;
}


int Field::getCurrentBeginY()
{
    return currentSizeY;
}

int Field::getCurrentSizeX()
{
    return currentSizeX;
}


int Field::getCurrentSizeY()
{
    return currentSizeY;
}

int Field::getFullSizeX()
{
    return fullSizeX;
}


int Field::getFullSizeY()
{
    return fullSizeY;
}

void Field::moveFieldUp() 
{
    if (currentBeginX != 0) {
        currentBeginX--;
        currentSizeX--;
    }
}

void Field::moveFieldDown() 
{
    if (currentSizeX != fullSizeX) {
        currentBeginX++;
        currentSizeX++;
    }
}

void Field::moveFieldLeft()
{
    if (currentBeginY != 0) {
        currentBeginY--;
        currentSizeY--;
    }
}

void Field::moveFieldRight()
{    
    if (currentSizeY != fullSizeY) {
        currentBeginY++;
        currentSizeY++;
    }

}

int Field::getCell(int cellX, int cellY)
{
    return fieldMap[cellX][cellY];
}


void Field::setCell(int cellX, int cellY, int color)
{
    fieldMap[cellX][cellY] = color;
}