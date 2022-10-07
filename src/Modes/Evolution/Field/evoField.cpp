#include "evoField.h"


void EvoField::drawCell(int cellX, int cellY)
{
    if(getCell(cellX, cellY) == Field::Free){
        currentScreen.setColor(evolutionParameters.freeCellColor, evolutionParameters.freeCellColor);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (getCell(cellX, cellY) == Field::Wall){
        currentScreen.setColor(evolutionParameters.wallCellColor, evolutionParameters.wallCellColor);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (getCell(cellX, cellY) == Field::Snake){
        currentScreen.setColor(evolutionParameters.snakeCellColor, evolutionParameters.snakeCellColor);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (getCell(cellX, cellY) == Field::Food){
        currentScreen.setColor(evolutionParameters.foodCellColor, evolutionParameters.foodCellColor);
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


void EvoField::drawSnakeAndFood()
{
    for(int countX = currentBeginX; countX < currentSizeX; countX++){
        for(int countY = currentBeginY; countY < currentSizeY; countY++){
            if (fieldMap[countX][countY] == Field::Snake || fieldMap[countX][countY] == Field::Food){
                drawCell(countX, countY);
            }
        }
    }
}