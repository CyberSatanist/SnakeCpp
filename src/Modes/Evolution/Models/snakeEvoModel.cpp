#include "snakeEvoModel.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;


void SnakeEvoModel::init(int startX, int startY, int length, int color)
{
    initField();
    initFood();

    snakeId = evolutionParameters.snakeIdCounter;
    evolutionParameters.snakeIdCounter++;

    currentBody->prevCell = NULL;
    snakeHeadTail->firstCell = currentBody;
    snakeTmp = currentBody;
    for (int x = 0; x < evolutionParameters.snakeLength; x++)
    { 
        snakeTmp->cellX = startX + x;
        snakeTmp->cellY = startY;
        field.setCell(startX + x, startY, Field::Snake);
        snakeBody* next = new snakeBody; 
        snakeTmp->nextCell = next;	
        next->prevCell = snakeTmp;	
        snakeTmp = next;
    }
    snakeTmp->nextCell = NULL;
    snakeHeadTail->lastCell = snakeTmp;

    isAlive = true;
    evolutionParameters.aliveSnakes++;
}

void SnakeEvoModel::drawField()
{
    field.drawField();
}

void SnakeEvoModel::drawStuff()
{
    field.drawSnakeAndFood();
}


void SnakeEvoModel::getSnakeHeadCoordinates(int* x, int* y)
{
    *x = snakeHeadTail->firstCell->cellX;
    *y = snakeHeadTail->firstCell->cellY;
}


void SnakeEvoModel::newCell()
{
    snakeBody* next = new snakeBody;
    next->nextCell = NULL;
    next->cellX = snakeHeadTail->lastCell->cellX;
    next->cellY = snakeHeadTail->lastCell->cellY;
    next->prevCell = snakeHeadTail->lastCell;
    snakeHeadTail->lastCell->nextCell = next;
    snakeHeadTail->lastCell = next;
}


void SnakeEvoModel::move()
{
    snakeTmp = snakeHeadTail->lastCell;
    field.setCell(snakeTmp->cellX, snakeTmp->cellY, Field::Free);
    while(snakeTmp->prevCell)
    {
        snakeTmp->cellX = snakeTmp->prevCell->cellX;
        snakeTmp->cellY = snakeTmp->prevCell->cellY;
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
    snakeHeadTail->firstCell = snakeTmp;
    validation();
    
}


void SnakeEvoModel::validation()
{
    snakeTmp = snakeHeadTail->firstCell;
    if (field.getCell(snakeTmp->cellX, snakeTmp->cellY) == Field::Wall) {
        death();
    } else if (field.getCell(snakeTmp->cellX, snakeTmp->cellY) == Field::Snake) {
        death();
    } else if (field.getCell(snakeTmp->cellX, snakeTmp->cellY) == Field::Free){
        field.setCell(snakeTmp->cellX, snakeTmp->cellY, Field::Snake);
    } else if (field.getCell(snakeTmp->cellX, snakeTmp->cellY) == Field::Food){
        snakeEat();
    }
}


void SnakeEvoModel::setVector(int direction)
{
    float vetc = network.useMind(field, snakeHeadTail->firstCell->cellX, snakeHeadTail->firstCell->cellY);

    if (vetc >= 0.5){
        direction = Screen::controll_keys::RIGHT;
    } else if (vetc < 0.5 & vetc >= 0){
        direction = Screen::controll_keys::UP;
    } else if (vetc < 0 & vetc >= -0.5){
        direction = Screen::controll_keys::LEFT;
    } else if (vetc < -0.5){
        direction = Screen::controll_keys::DOWN;
    }

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


void SnakeEvoModel::initField()
{
    field.initField(
        evolutionParameters.currentFieldSizeX,
        evolutionParameters.currentFieldSizeY,
        evolutionParameters.fullFieldSizeX,
        evolutionParameters.fullFieldSizeY
    );
    field.initEvoField();
}


void SnakeEvoModel::initFood()
{
    food = new foodList;
    foodTmp = food;
    for (int count = 0; count < evolutionParameters.countOfFood; count++)
    {
        FoodEvoModel newFood;
        newFood.init((field.getFullSizeX() - 2), (field.getFullSizeY() - 2), evolutionParameters.snakeOnefoodColor);
        field.setCell(newFood.cellX(), newFood.cellY(), Field::Food);
        foodTmp->currentFood = newFood;
        foodTmp->nextFood = new foodList;
        foodTmp = foodTmp->nextFood;
        foodTmp->nextFood = NULL;
    }
}

void SnakeEvoModel::snakeEat()
{
    newCell();
    newFood();
    score += 10;
    if (score > evolutionParameters.score){
        evolutionParameters.score = score;
        evolutionParameters.bestSnakeId = snakeId;
    }
}


void SnakeEvoModel::newFood()
{
    int foodX = food->currentFood.randX();
    int foodY = food->currentFood.randY();
    while (field.getCell(foodX, foodY) != Field::Free){
        foodX = food->currentFood.randX();
        foodY = food->currentFood.randY();
    }
    field.setCell(foodX, foodY, Field::Food);
}


void SnakeEvoModel::death()
{
    isAlive = false;
    evolutionParameters.aliveSnakes--;
}
