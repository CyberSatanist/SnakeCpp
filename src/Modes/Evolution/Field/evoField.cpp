#include "evoField.h"


void EvoField::drawCell(int cellX, int cellY)
{
    if(getCell(cellX, cellY) == Field::Free){
        currentScreen.setColor(COLOR_WHITE, COLOR_WHITE);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (getCell(cellX, cellY) == Field::Wall){
        currentScreen.setColor(COLOR_BLUE, COLOR_BLUE);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (getCell(cellX, cellY) == Field::Snake){
        currentScreen.setColor(COLOR_GREEN, COLOR_GREEN);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (getCell(cellX, cellY) == Field::Food){
        currentScreen.setColor(COLOR_RED, COLOR_RED);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    }
}


void EvoField::initEvoField()
{
    for (int countX = 0; countX < fullSizeX; countX++) {
        for (int countY = 0; countY < fullSizeY; countY++) {
            if ((countX == 0) || (countY == 0) || (countX == (fullSizeX - 1)) || (countY == (fullSizeY - 1))) {
                setCell(countX, countY, Field::Wall);
            }
        }
    }
}