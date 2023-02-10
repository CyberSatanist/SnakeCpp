#include <random>
#include "lifeField.h"
#include "LifeGame/Parameters/lifeGameParameters.h"

extern LifeGameParameters lifeGameParameters;


LifeField::LifeField(int currentX, int currentY, int fullX, int fullY) : Field(currentX, currentY, fullX, fullY)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(0, 100);
    lifeGameParameters.cellsCount = 0;

    for (int countX = 0; countX < fullSizeX; countX++){
        for (int countY = 0; countY < fullSizeY; countY++){
            int randChance = randGen(generator);
            if (randChance <= lifeGameParameters.cellStartBornChance) {
                fieldMap[countX][countY] = Field::Cell;
                lifeGameParameters.cellsCount++;
            } else {
                fieldMap[countX][countY] = Field::Free;
            }
        }
    }
}


void LifeField::makeTurn()
{
    int **newField;
    lifeGameParameters.cellsCount = 0;

    newField = new int* [fullSizeX];
    for (int countX = 0; countX < fullSizeX; countX++){
        newField[countX] = new int [fullSizeY];
        for (int countY = 0; countY < fullSizeY; countY++){
            int neighborsCount = 0;
            for (int currentX = (countX - 1); currentX <= (countX + 1); currentX++){
                for (int currentY = (countY - 1); currentY <= (countY + 1); currentY++){
                    if ((currentX > -1) && (currentY > -1) && (currentX < fullSizeX) && (currentY < fullSizeY)){
                        if (fieldMap[currentX][currentY] == Field::Cell){
                            neighborsCount++;
                        }
                    }
                }
            }
            if ((neighborsCount > 2) && (neighborsCount < 5)) {
                newField[countX][countY] = Field::Cell;
                lifeGameParameters.cellsCount++;
            } else {
                newField[countX][countY] = Field::Free;
            }
        }
    }

    for (int x = 0; x < fullSizeX; x++){
            delete[] fieldMap[x];
            
        }
    delete[] fieldMap;

    fieldMap = newField;
}


void LifeField::reset()
{
    if (fieldMap){
        for (int x = 0; x < fullSizeX; x++){
            delete[] fieldMap[x];
        }
        delete[] fieldMap;
    }

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(0, 100);
    lifeGameParameters.cellsCount = 0;

    fieldMap = new int* [fullSizeX];
    for (int countX = 0; countX < fullSizeX; countX++){
        fieldMap[countX] = new int [fullSizeY];
        for (int countY = 0; countY < fullSizeY; countY++){
            int randChance = randGen(generator);
            if (randChance <= lifeGameParameters.cellStartBornChance) {
                fieldMap[countX][countY] = Field::Cell;
                lifeGameParameters.cellsCount++;
            } else {
                fieldMap[countX][countY] = Field::Free;
            }
        }
    }
}


void LifeField::clean()
{
    for (int countX = 0; countX < fullSizeX; countX++){
        for (int countY = 0; countY < fullSizeY; countY++){
            fieldMap[countX][countY] = Field::Free;
        }
    }
}


bool LifeField::onFrame(int x, int y) const
{
    if(
        (x == currentBeginX && y >= currentBeginY && y <= currentSizeY)
        || (x == currentSizeX && y >= currentBeginY && y <= currentSizeY)
        || (y == currentBeginY && x >= currentBeginX && x <= currentSizeX)
        || (y == currentSizeY && x >= currentBeginX && x <= currentSizeX)
    ){
        return true;
    }
    return false;
}

void LifeField::drawCellsHandler(int key)
{
    if (!isCursorSet) {
        isCursorSet = true;
        cursorX = currentBeginX;
        cursorY = currentBeginY;
    }

    currentScreen.setColor(COLOR_GREEN, COLOR_GREEN);
    currentScreen.setCursor(cursorX - currentBeginX, cursorY - currentBeginY);
    currentScreen.writeText(" ");

    switch(key){
        case Screen::controll_keys::UP:
            if (cursorX < currentBeginX){
                cursorX = currentSizeX - 1;
            } else {
                cursorX--;
            }
            break;
        case Screen::controll_keys::DOWN:
            if (cursorX > currentSizeX){
                cursorX = currentBeginX;
            } else {
                cursorX++;
            }
            break;
        case Screen::controll_keys::LEFT:
            if (cursorY < currentBeginY){
                cursorY = currentSizeY - 1;
            } else {
                cursorY--;
            }
            break;
        case Screen::controll_keys::RIGHT:
            if (cursorY > currentSizeY){
                cursorY = currentBeginY;
            } else {
                cursorY++;
            }
            break;
        case Screen::controll_keys::SELECT:
            if (getCell(cursorX, cursorY) == Field::Cell){
                setCell(cursorX, cursorY, Field::Free);
            } else {
                setCell(cursorX, cursorY, Field::Cell);
            }
            break;
        case Screen::controll_keys::ESCAPE:
            lifeGameParameters.drawCells = false;
            lifeGameParameters.pauseOn = false;
            isCursorSet = false;
            break;
    }

}


void LifeField::moveHandler(int key){
    switch(key){
        case Screen::controll_keys::UP:
            moveFieldUp();
            break;
        case Screen::controll_keys::DOWN:
            moveFieldDown();
            break;
        case Screen::controll_keys::LEFT:
            moveFieldLeft();
            break;
        case Screen::controll_keys::RIGHT:
            moveFieldRight();
            break;
        case Screen::controll_keys::ESCAPE:
            lifeGameParameters.moveField = false;
            break;
    }
}


void LifeField::drawCell(int cellX, int cellY) 
{
    if(getCell(cellX + currentBeginX, cellY + currentBeginY) == Field::Free){
        currentScreen.setColor(COLOR_WHITE, COLOR_WHITE);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    } else if (getCell(cellX + currentBeginX, cellY + currentBeginY) == Field::Cell){
        currentScreen.setColor(COLOR_BLUE, COLOR_BLUE);
        currentScreen.setCursor(cellX, cellY);
        currentScreen.writeText(" ");
    }
}