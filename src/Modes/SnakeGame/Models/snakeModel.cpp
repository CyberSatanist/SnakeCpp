#include "snakeModel.h"

extern SnakeParameters snakeParameters;

void SnakeModel::init(Screen screen)
{
    currentScreen = screen;
    currentBody->prevCell = NULL;
    snakeHeadTail->firstCell = currentBody;
    snakeTmp = currentBody;
    for (int x = 0; x < snakeParameters.snakeLength; x++)
    { 
        snakeTmp->cellY = currentScreen.getWidth() / 2;
        snakeTmp->cellX = (currentScreen.getHight() / 2) + x;
        snakeBody* next = new snakeBody; 
        snakeTmp->nextCell = next;	
        next->prevCell = snakeTmp;	
        snakeTmp = next;	
    }
    snakeTmp->nextCell = NULL;
    snakeHeadTail->lastCell = snakeTmp;
}


void SnakeModel::drawSnake()
{
    snakeTmp = currentBody;
    currentScreen.setColor(snakeParameters.whiteColor, snakeParameters.snakeHeadColor);
    currentScreen.setCursor(snakeTmp->cellX, snakeTmp->cellY);
    currentScreen.writeText(" ");
    snakeTmp = snakeTmp->nextCell;
    int colorCount = 0;
    while(snakeTmp->nextCell) {
        if (colorCount == 0) {
            currentScreen.setColor(snakeParameters.whiteColor, snakeParameters.snakeBodyColorOne);
            colorCount = 1;
        } else {
            currentScreen.setColor(snakeParameters.whiteColor, snakeParameters.snakeBodyColorTwo);
            colorCount = 0;
        }
        currentScreen.setCursor(snakeTmp->cellX, snakeTmp->cellY);
        currentScreen.writeText(" ");
        snakeTmp = snakeTmp->nextCell;
    }
}


void SnakeModel::getSnakeHeadCoordinates(int* x, int* y)
{
    *x = snakeHeadTail->firstCell->cellX;
    *y = snakeHeadTail->firstCell->cellY;
}


void SnakeModel::newCell()
{
    snakeBody* next = new snakeBody;
    next->nextCell = NULL;
    next->cellX = snakeHeadTail->lastCell->cellX;
    next->cellY = snakeHeadTail->lastCell->cellY;
    next->prevCell = snakeHeadTail->lastCell;
    snakeHeadTail->lastCell->nextCell = next;
    snakeHeadTail->lastCell = next;
}


void SnakeModel::move()
{
    snakeTmp = snakeHeadTail->lastCell;
    while(snakeTmp->prevCell)
    {
        snakeTmp->cellX = snakeTmp->prevCell->cellX;
        snakeTmp->cellY = snakeTmp->prevCell->cellY;
        wallValidation(snakeTmp);
        snakeTmp = snakeTmp->prevCell;
    }

    switch(snakeTmp->vector) {
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
    wallValidation(snakeTmp);
}


void SnakeModel::wallValidation(snakeBody* snakeTmp)
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


void SnakeModel::setVector(Screen::controll_keys vector)
{
    switch (vector) {
        case Screen::controll_keys::RIGHT:
            if(currentBody->vector != Screen::controll_keys::LEFT) {
                currentBody->vector = vector;
            }
            break;
        case Screen::controll_keys::LEFT:
            if(currentBody->vector != Screen::controll_keys::RIGHT) {
                currentBody->vector = vector;
            }
            break; 
        case Screen::controll_keys::UP:
            if(currentBody->vector != Screen::controll_keys::DOWN) {
                currentBody->vector = vector;
            }
            break;
        case Screen::controll_keys::DOWN:
            if(currentBody->vector != Screen::controll_keys::UP) {
                currentBody->vector = vector;
            }
            break;
    }
}


bool SnakeModel::deathCheck()
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
