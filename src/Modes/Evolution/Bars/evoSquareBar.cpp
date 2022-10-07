#include "evoSquareBar.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;


void EvoSquareBar::initField(Field thatField)
{
    field = thatField;
    mapSizeX = squareBarXEnd - squareBarXStart;
    mapSizeY = squareBarYEnd - squareBarYStart;
    fieldSizeX = field.fullSizeX;
    fieldSizeY = field.fullSizeY;
    stepX =  fieldSizeX / mapSizeX + 1;
    stepY =  fieldSizeY / mapSizeY + 1;
}

void EvoSquareBar::drawMap(Field thatField)
{
    field = thatField;

    for (int x = squareBarXStart; x < squareBarXEnd; x++){
        currentScreen.setCursor(x, squareBarYStart - 1);
        currentScreen.setColor(COLOR_YELLOW, COLOR_YELLOW);
        currentScreen.writeText(" ");
    }
    for (int y = squareBarYStart ; y < squareBarYEnd; y++){
        currentScreen.setCursor(squareBarXStart - 1, y);
        currentScreen.setColor(COLOR_YELLOW, COLOR_YELLOW);
        currentScreen.writeText(" ");
    }

    for (int mapX = squareBarXStart, x = 0; mapX < squareBarXEnd; mapX++, x++){
        for (int mapY = squareBarYStart, y = 0; mapY < squareBarYEnd; mapY++, y++){
            drawCell(mapX, mapY, getColor(x, y, stepX, stepY));
        }
    }
}


void EvoSquareBar::drawCell(int cellX, int cellY, int color)
{
    if(color == Field::Free){
        currentScreen.setColor(evolutionParameters.freeCellColor, evolutionParameters.freeCellColor);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (color == Field::Wall){
        currentScreen.setColor(evolutionParameters.wallCellColor, evolutionParameters.wallCellColor);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (color == Field::Snake){
        currentScreen.setColor(evolutionParameters.snakeCellColor, evolutionParameters.snakeCellColor);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (color == Field::Food){
        currentScreen.setColor(evolutionParameters.foodCellColor, evolutionParameters.foodCellColor);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (color == Field::Nothing){
        currentScreen.setColor(COLOR_YELLOW, COLOR_YELLOW);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    }
}


int EvoSquareBar::getColor(int mapX, int mapY, int stepX, int stepY)
{
    bool wall = false;
    bool food = false;
    bool free = false;
    for (int countX = (mapX * stepX); countX < (mapX * stepX + stepX); countX++){
        if (countX >= 0 & countX <= (field.fullSizeX - 1)) {
            for (int countY = (mapY * stepY); countY < (mapY * stepY + stepY); countY++) {
                if (countY >= 0 & countY <= (field.fullSizeY - 1)) {
                    if (field.getCell(countX, countY) == Field::Snake){
                        return Field::Snake;
                    }
                    if (field.getCell(countX, countY) == Field::Wall){
                        wall = true;
                    } else if (field.getCell(countX, countY) == Field::Food){
                        food  = true;
                    } else if (field.getCell(countX, countY) == Field::Free){
                        free  = true;
                    }
                }
            }
        }
    }
    if (food){
        return Field::Food;
    }
    if (wall){
        return Field::Wall;
    }
    if (free){
        return Field::Free;
    }
    return Field::Nothing;

}