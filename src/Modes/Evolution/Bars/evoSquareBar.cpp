#include "evoSquareBar.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;


EvoSquareBar::EvoSquareBar(int xStart, int yStart, int xEnd, int yEnd)
    : SquareBar(xStart, yStart, xEnd, yEnd)
{
    mapSizeX = endX - startX;
    mapSizeY = endY - startY;
}

void EvoSquareBar::drawMap(const Field &field)
{
    drawBorders();

    fieldSizeX = field.getFullSizeX();
    fieldSizeY = field.getFullSizeY();
    stepX =  fieldSizeX / mapSizeX + 1;
    stepY =  fieldSizeY / mapSizeY + 1;

    for (int mapX = startX + 1, x = 0; mapX < endX - 1; mapX++, x++){
        for (int mapY = startY + 1, y = 0; mapY < endY - 1; mapY++, y++){
            drawCell(mapX, mapY, getColor(x, y, stepX, stepY, field));
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


int EvoSquareBar::getColor(int mapX, int mapY, int stepX, int stepY, const Field &field)
{
    bool wall = false;
    bool food = false;
    bool free = false;
    for (int countX = (mapX * stepX); countX < (mapX * stepX + stepX); countX++){
        if ((countX >= 0) && (countX <= (fieldSizeX - 1))) {
            for (int countY = (mapY * stepY); countY < (mapY * stepY + stepY); countY++) {
                if ((countY >= 0) && (countY <= (fieldSizeY - 1))) {
                    switch(field.getCell(countX, countY)) {
                        case Field::Snake:
                            return Field::Snake;
                        case Field::Wall:
                            wall = true;
                            break;
                        case Field::Food:
                            food  = true;
                            break;
                        case Field::Free:
                            free  = true;
                            break;
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