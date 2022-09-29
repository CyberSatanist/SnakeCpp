#include "lifeField.h"


void LifeField::drawCell(int cellX, int cellY) 
{
    if(getCell(cellX, cellY) == Field::Free){
        currentScreen.setColor(COLOR_WHITE, COLOR_WHITE);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (getCell(cellX, cellY) == Field::Cell){
        currentScreen.setColor(COLOR_BLUE, COLOR_BLUE);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    }
}