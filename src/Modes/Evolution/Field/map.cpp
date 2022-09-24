#include "map.h"
#include <unistd.h>


void Map::initMap(int sizeX, int sizeY)
{
    mapSizeX = sizeX;
    mapSizeY = sizeY;
    fieldMap = new int* [sizeX];
    for (int countX = 0; countX < sizeX; countX++){
        fieldMap[countX] = new int [sizeY];
        for (int countY = 0; countY < sizeY; countY++){
            if ((countX == 0 | countX == sizeX - 1) | (countY == 0 | countY == sizeY - 1)){
                fieldMap[countX][countY] = Wall;
            } else {
                fieldMap[countX][countY] = Free;
            }
        }
    }
}


int Map::getSizeX()
{
    return mapSizeX;
}


int Map::getSizeY()
{
    return mapSizeY;
}


int Map::getCell(int cellX, int cellY)
{
    return fieldMap[cellX][cellY];
}


void Map::setCell(int cellX, int cellY, int color)
{
    fieldMap[cellX][cellY] = color;
}