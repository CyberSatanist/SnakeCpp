#include "map.h"


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


void Map::drawField()
{
    for(int countX = 0; countX < mapSizeX; countX++){
        for(int countY = 0; countY < mapSizeY; countY++){
            if(getCell(countX, countY) == Map::Free){
                currentScreen.setColor(COLOR_WHITE, COLOR_WHITE);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            } else if (getCell(countX, countY) == Map::Wall){
                currentScreen.setColor(COLOR_BLUE, COLOR_BLUE);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            } else if (getCell(countX, countY) == Map::Snake){
                currentScreen.setColor(COLOR_GREEN, COLOR_GREEN);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            } else if (getCell(countX, countY) == Map::Food){
                currentScreen.setColor(COLOR_RED, COLOR_RED);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
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