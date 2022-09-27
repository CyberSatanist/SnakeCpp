#include "lifeMap.h"


void LifeMap::initMap(int sizeX, int sizeY)
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


void LifeMap::drawField()
{
    for(int countX = 0; countX < mapSizeX; countX++){
        for(int countY = 0; countY < mapSizeY; countY++){
            if(getCell(countX, countY) == LifeMap::Free){
                currentScreen.setColor(COLOR_WHITE, COLOR_WHITE);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            } else if (getCell(countX, countY) == LifeMap::Wall){
                currentScreen.setColor(COLOR_BLUE, COLOR_BLUE);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            } else if (getCell(countX, countY) == LifeMap::Snake){
                currentScreen.setColor(COLOR_GREEN, COLOR_GREEN);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            } else if (getCell(countX, countY) == LifeMap::Food){
                currentScreen.setColor(COLOR_RED, COLOR_RED);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            }
        }
    }
}


int LifeMap::getSizeX()
{
    return mapSizeX;
}


int LifeMap::getSizeY()
{
    return mapSizeY;
}


int LifeMap::getCell(int cellX, int cellY)
{
    return fieldMap[cellX][cellY];
}


void LifeMap::setCell(int cellX, int cellY, int color)
{
    fieldMap[cellX][cellY] = color;
}
