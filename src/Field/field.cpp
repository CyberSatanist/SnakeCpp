#include "field.h"


Field::Field(int currentX, int currentY, int fullX, int fullY)
{
    sizeX = currentSizeX = currentX;
    sizeY = currentSizeY = currentY;
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


Field::Field(const Field &field)
{
    if (&field == this){
        return;
    }
    
    if (fieldMap){
        for (int x = 0; x < fullSizeX; x++){
            delete[] fieldMap[x];
            
        }
        delete[] fieldMap;
    }

    beginX = currentBeginX = field.getBeginX();
    beginY = currentBeginY = field.getBeginY();
    sizeX = currentSizeX = field.getSizeX();
    sizeY = currentSizeY = field.getSizeY();
    fullSizeX = field.getFullSizeX();
    fullSizeY = field.getFullSizeY();

    fieldMap = new int* [fullSizeX];
    for (int countX = 0; countX < fullSizeX; countX++){
        fieldMap[countX] = new int [fullSizeY];
        for (int countY = 0; countY < fullSizeY; countY++){
            fieldMap[countX][countY] = field.getCell(countX, countY);
        }
    }
}


Field& Field::operator=(const Field &field)
{
    if (&field == this){
        return *this;
    }
    
    if (fieldMap){
        for (int x = 0; x < fullSizeX; x++){
            delete[] fieldMap[x];
        }
        delete[] fieldMap;
    }

    beginX = currentBeginX = field.getBeginX();
    beginY = currentBeginY = field.getBeginY();
    sizeX = currentSizeX = field.getSizeX();
    sizeY = currentSizeY = field.getSizeY();
    fullSizeX = field.getFullSizeX();
    fullSizeY = field.getFullSizeY();

    fieldMap = new int* [fullSizeX];
    for (int countX = 0; countX < fullSizeX; countX++){
        fieldMap[countX] = new int [fullSizeY];
        for (int countY = 0; countY < fullSizeY; countY++){
            fieldMap[countX][countY] = field.getCell(countX, countY);
        }
    }
    return *this;
}


Field::~Field()
{
    if (fieldMap){
        for (int x = 0; x < fullSizeX; x++){
            delete[] fieldMap[x];
        }
        delete[] fieldMap;
    }
}


void Field::drawField()
{
    for(int countX = beginX; countX < sizeX; countX++){
        for(int countY = beginY; countY < sizeY; countY++){
            drawCell(countX, countY);
        }
    }
}


void Field::moveFieldUp() 
{
    if (currentBeginX > 0) {
        currentBeginX--;
        currentSizeX--;
    }
}

void Field::moveFieldDown() 
{
    if (currentSizeX < fullSizeX) {
        currentBeginX++;
        currentSizeX++;
    }
}

void Field::moveFieldLeft()
{
    if (currentBeginY > 0) {
        currentBeginY--;
        currentSizeY--;
    }
}

void Field::moveFieldRight()
{    
    if (currentSizeY < fullSizeY) {
        currentBeginY++;
        currentSizeY++;
    }

}
