#include "snakeModel.h"

extern SnakeParameters snakeParameters;

void SnakeModel::init(Screen screen)
{
    currentScreen = screen;
    currentBody->prevCell = NULL;
    snakeHeadTail->firstCell = currentBody;
    tmp = currentBody;
    for (int x = 0; x < snakeParameters.snakeLength; x++)
    { 
        tmp->cellY = currentScreen.getWidth() / 2;
        tmp->cellX = (currentScreen.getHight() / 2) + x;
        snakeBody* next = new snakeBody; 
        tmp->nextCell = next;	
        next->prevCell = tmp;	
        tmp = next;	
    }
    tmp->nextCell = NULL;
    snakeHeadTail->lastCell = tmp;
}


void SnakeModel::drawSnake()
{
    tmp = currentBody;
    currentScreen.setColor(snakeParameters.whiteColor, snakeParameters.snakeHeadColor);
    currentScreen.setCursor(tmp->cellX, tmp->cellY);
    currentScreen.writeText(" ");
    tmp = tmp->nextCell;
    int x = 0;
    while(tmp->nextCell) {
	if (x == 0) {
            currentScreen.setColor(snakeParameters.whiteColor, snakeParameters.snakeBodyColorOne);
	    x = 1;
	} else {
            currentScreen.setColor(snakeParameters.whiteColor, snakeParameters.snakeBodyColorTwo);
	    x = 0;
	}
        currentScreen.setCursor(tmp->cellX, tmp->cellY);
        currentScreen.writeText(" ");
        tmp = tmp->nextCell;
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
    tmp = snakeHeadTail->lastCell;
    while(tmp->prevCell)
    {
        tmp->cellX = tmp->prevCell->cellX;
        tmp->cellY = tmp->prevCell->cellY;
        wallValidation(tmp);
        tmp = tmp->prevCell;
    }

    switch(tmp->vector) {
    case Screen::controll_keys::UP:
        if (tmp->nextCell->cellX != tmp->cellX - 1) {
            tmp->cellX = tmp->cellX -1;
        }
        break;
    case Screen::controll_keys::DOWN:
        if (tmp->nextCell->cellX != tmp->cellX + 1) {
            tmp->cellX = tmp->cellX + 1;
        }
        break;
    case Screen::controll_keys::LEFT:
        if (tmp->nextCell->cellY != tmp->cellY - 1) {
            tmp->cellY = tmp->cellY - 1;
        }
        break;
    case Screen::controll_keys::RIGHT:
        if (tmp->nextCell->cellY != tmp->cellY + 1) {
            tmp->cellY = tmp->cellY + 1;
        }
        break;
    }
    wallValidation(tmp);
}


void SnakeModel::wallValidation(snakeBody* tmp)
{
    if (tmp->cellX < 0) {
         tmp->cellX = currentScreen.getHight() -1;
    } else if (tmp->cellX > currentScreen.getHight()-1) {
        tmp->cellX = 0;
    }
    if (tmp->cellY < 0) {
        tmp->cellY = currentScreen.getWidth() -1;
    } else if (tmp->cellY > currentScreen.getWidth()-1) {
        tmp->cellY = 0;
    }
}


void SnakeModel::setVector(Screen::controll_keys vector)
{
    switch (vector)
    {
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
    tmp = snakeHeadTail->lastCell;
    while(tmp->prevCell) {
        if (tmp->cellX == snakeHeadTail->firstCell->cellX && tmp->cellY == snakeHeadTail->firstCell->cellY) {
            return true;
        }
        tmp = tmp->prevCell;
    }
    return false;
}
