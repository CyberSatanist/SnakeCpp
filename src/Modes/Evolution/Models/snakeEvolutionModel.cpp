#include "snakeEvolutionModel.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;

void SnakeEvolutionModel::init(int startX, int startY, int length, int color)
{
    currentBody->prevCell = NULL;
    snakeHeadTail->firstCell = currentBody;
    snakeTmp = currentBody;
    for (int x = 0; x < evolutionParameters.snakeLength; x++)
    { 
        snakeTmp->cellX = startX + x;
        snakeTmp->cellY = startY;
        snakeBody* next = new snakeBody; 
        snakeTmp->nextCell = next;	
        next->prevCell = snakeTmp;	
        snakeTmp = next;	
    }
    snakeTmp->nextCell = NULL;
    snakeHeadTail->lastCell = snakeTmp;
}


void SnakeEvolutionModel::drawSnake()
{
    snakeTmp = currentBody;
    currentScreen.setColor(evolutionParameters.whiteColor, evolutionParameters.snakeHeadColor);
    currentScreen.setCursor(snakeTmp->cellX, snakeTmp->cellY);
    currentScreen.writeText(" ");
    snakeTmp = snakeTmp->nextCell;
    int colorCount = 0;
    while(snakeTmp->nextCell) {
        if (colorCount == 0) {
            currentScreen.setColor(evolutionParameters.whiteColor, evolutionParameters.snakeOneBodyColor);
            colorCount = 1;
        } else {
            currentScreen.setColor(evolutionParameters.whiteColor, evolutionParameters.snakeOneBodyColor);
            colorCount = 0;
        }
        currentScreen.setCursor(snakeTmp->cellX, snakeTmp->cellY);
        currentScreen.writeText(" ");
        snakeTmp = snakeTmp->nextCell;
    }
}


void SnakeEvolutionModel::getSnakeHeadCoordinates(int* x, int* y)
{
    *x = snakeHeadTail->firstCell->cellX;
    *y = snakeHeadTail->firstCell->cellY;
}


void SnakeEvolutionModel::newCell()
{
    snakeBody* next = new snakeBody;
    next->nextCell = NULL;
    next->cellX = snakeHeadTail->lastCell->cellX;
    next->cellY = snakeHeadTail->lastCell->cellY;
    next->prevCell = snakeHeadTail->lastCell;
    snakeHeadTail->lastCell->nextCell = next;
    snakeHeadTail->lastCell = next;
}


void SnakeEvolutionModel::move()
{
    snakeTmp = snakeHeadTail->lastCell;
    while(snakeTmp->prevCell)
    {
        snakeTmp->cellX = snakeTmp->prevCell->cellX;
        snakeTmp->cellY = snakeTmp->prevCell->cellY;
        validation(snakeTmp);
        snakeTmp = snakeTmp->prevCell;
    }

    switch(vector) {
        case Screen::controll_keys::UP:
            if (snakeTmp->nextCell->cellX != snakeTmp->cellX - 1) {
                snakeTmp->cellX = snakeTmp->cellX -1;
            }
            break;
        case Screen::controll_keys::DOWN:
            if (snakeTmp->nextCell->cellX != snakeTmp->cellX + 1) {
                snakeTmp->cellX = snakeTmp->cellX + 1;
            }
            break;
        case Screen::controll_keys::LEFT:
            if (snakeTmp->nextCell->cellY != snakeTmp->cellY - 1) {
                snakeTmp->cellY = snakeTmp->cellY - 1;
            }
            break;
        case Screen::controll_keys::RIGHT:
            if (snakeTmp->nextCell->cellY != snakeTmp->cellY + 1) {
                snakeTmp->cellY = snakeTmp->cellY + 1;
            }
            break;
    }
    validation(snakeTmp);
}


void SnakeEvolutionModel::validation(snakeBody* snakeTmp)
{
    if (snakeTmp->cellX < 0) {
        snakeTmp->cellX = currentScreen.getHight() -1;
    } else if (snakeTmp->cellX > currentScreen.getHight()-1) {
        snakeTmp->cellX = 0;
    }
    if (snakeTmp->cellY < 0) {
        snakeTmp->cellY = currentScreen.getWidth() -1;
    } else if (snakeTmp->cellY > currentScreen.getWidth()-1) {
        snakeTmp->cellY = 0;
    }
}


void SnakeEvolutionModel::setVector(int direction)
{
    switch (direction) {
        case Screen::controll_keys::RIGHT:
            if(vector != Screen::controll_keys::LEFT) {
                vector = direction;
            }
            break;
        case Screen::controll_keys::LEFT:
            if(vector != Screen::controll_keys::RIGHT) {
                vector = direction;
            }
            break; 
        case Screen::controll_keys::UP:
            if(vector != Screen::controll_keys::DOWN) {
                vector = direction;
            }
            break;
        case Screen::controll_keys::DOWN:
            if(vector != Screen::controll_keys::UP) {
                vector = direction;
            }
            break;
    }
}


bool SnakeEvolutionModel::deathCheck()
{
    snakeTmp = snakeHeadTail->lastCell;
    while(snakeTmp->prevCell) {
        if (snakeTmp->cellX == snakeHeadTail->firstCell->cellX && snakeTmp->cellY == snakeHeadTail->firstCell->cellY) {
            return true;
        }
        snakeTmp = snakeTmp->prevCell;
    }
    return false;
}
