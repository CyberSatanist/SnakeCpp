#include "lifeSquareBar.h"
#include "LifeGame/Parameters/lifeGameParameters.h"

extern LifeGameParameters lifeGameParameters;


LifeSquareBar::LifeSquareBar(int xStart, int yStart, int xEnd, int yEnd)
    : SquareBar(xStart, yStart, xEnd, yEnd)
{
    mapSizeX = endX - startX;
    mapSizeY = endY - startY;
}

void LifeSquareBar::drawMap(const LifeField &field)
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


void LifeSquareBar::drawCell(int cellX, int cellY, int color)
{
    if(color == Field::Free){
        currentScreen.setColor(lifeGameParameters.freeCellColor, lifeGameParameters.freeCellColor);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (color == Field::Cell){
        currentScreen.setColor(lifeGameParameters.cellColor, lifeGameParameters.cellColor);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (color == Field::Frame){
        currentScreen.setColor(lifeGameParameters.frameColor, lifeGameParameters.frameColor);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    }
}


int LifeSquareBar::getColor(int mapX, int mapY, int stepX, int stepY, const LifeField &field)
{
    bool cell = false;
    for (int countX = (mapX * stepX); countX < (mapX * stepX + stepX); countX++){
        if ((countX >= 0) && (countX <= (fieldSizeX - 1))) {
            for (int countY = (mapY * stepY); countY < (mapY * stepY + stepY); countY++) {
                if ((countY >= 0) && (countY <= (fieldSizeY - 1))) {
                    if (field.onFrame(countX, countY)){
                        return Field::Frame;
                    }
                    if (field.getCell(countX, countY) == Field::Cell) {
                        cell = true;
                    }
                }
            }
        }
    }

    if (cell){
        return Field::Cell;
    }

    return Field::Free;
}