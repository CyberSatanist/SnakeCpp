#include "snakeEvoModel.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;


SnakeEvoModel::SnakeEvoModel(int startX, int startY, int length, int color)
    : field(evolutionParameters.currentFieldSizeX, evolutionParameters.currentFieldSizeY, evolutionParameters.fullFieldSizeX, evolutionParameters.fullFieldSizeY)
{
    snakeId = evolutionParameters.snakeIdCounter;
    evolutionParameters.snakeIdCounter++;
}


void SnakeEvoModel::init(int startX, int startY, int length, int color)
{
    delete currentBody; 

    currentBody = new snakeBody;

    currentBody->prevCell = NULL;

    snakeHeadTail = new snakeLocs;
    
    snakeHeadTail->firstCell = currentBody;
	snakeBody* snakeTmp = nullptr;
    snakeTmp = currentBody;
    for (int x = 0; x < evolutionParameters.snakeLength; x++)
    { 
        snakeTmp->cellX = startX + x;
        snakeTmp->cellY = startY;
        field.setCell(startX + x, startY, Field::Snake);
        snakeTmp->nextCell = new snakeBody;	
        snakeTmp->nextCell->prevCell = snakeTmp;	
        snakeTmp = snakeTmp->nextCell;
    }
    snakeTmp->nextCell = NULL;
    snakeHeadTail->lastCell = snakeTmp->prevCell;

    isAlive = true;
    evolutionParameters.aliveSnakes++;
    initFood();
    initBorders();
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
	snakeBody* snakeTmp = nullptr;
    snakeTmp = new snakeBody;
    snakeTmp->nextCell = NULL;
    snakeTmp->cellX = snakeHeadTail->lastCell->cellX;
    snakeTmp->cellY = snakeHeadTail->lastCell->cellY;
    snakeTmp->prevCell = snakeHeadTail->lastCell;
    snakeHeadTail->lastCell->nextCell = snakeTmp;
    snakeHeadTail->lastCell = snakeTmp;
}


void SnakeEvoModel::move()
{
	snakeBody* snakeTmp = nullptr;

    snakeTmp = snakeHeadTail->lastCell;
    field.setCell(snakeTmp->cellX, snakeTmp->cellY, Field::Free);
    while(snakeTmp->prevCell)
    {
        snakeTmp->cellX = snakeTmp->prevCell->cellX;
        snakeTmp->cellY = snakeTmp->prevCell->cellY;
        snakeTmp = snakeTmp->prevCell;
    }

    switch(this->vector) {
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
    turnsLeft -= 1;
    if (turnsLeft < 1){
        death();
    }
}


void SnakeEvoModel::validation()
{
	snakeBody* snakeTmp = nullptr;

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
    direction = network.useMind(field, snakeHeadTail->firstCell->cellX, snakeHeadTail->firstCell->cellY);

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


void SnakeEvoModel::initFood()
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGenX(field.getCurrentBeginX() + 1, field.getFullSizeX() - 1);
    std::uniform_int_distribution<> randGenY(field.getCurrentBeginY() + 1, field.getFullSizeY() - 1);
    int foodX = randGenX(generator);
    int foodY = randGenY(generator);

    for (int count = 0; count < evolutionParameters.countOfFood; count++)
    {
        while (field.getCell(foodX, foodY) != Field::Free){
            foodX = randGenX(generator);
            foodY = randGenY(generator);
        }
        field.setCell(foodX, foodY, Field::Food);
    }
}


void SnakeEvoModel::initBorders()
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGenX(field.getCurrentBeginX() + 1, field.getFullSizeX() - 1);
    std::uniform_int_distribution<> randGenY(field.getCurrentBeginY() + 1, field.getFullSizeY() - 1);
    int borderX = randGenX(generator);
    int borderY = randGenY(generator);

    for (int count = 0; count < evolutionParameters.countOfBorders; count++)
    {
        while (field.getCell(borderX, borderY) != Field::Free){
            borderX = randGenX(generator);
            borderY = randGenY(generator);
        }
        field.setCell(borderX, borderY, Field::Wall);
    }
}


void SnakeEvoModel::snakeEat()
{
    newCell();
    newFood();
    foodEaten++;
    turnsLeft += 100;
    if (turnsLeft > evolutionParameters.hightTurnsLeft){
        evolutionParameters.hightTurnsLeft = turnsLeft;
    }
    if (foodEaten > evolutionParameters.bestFood){
        evolutionParameters.bestFood = foodEaten;
    }
    if (score > evolutionParameters.score){
        evolutionParameters.score = score;
        evolutionParameters.bestSnakeId = snakeId;
    }
}


void SnakeEvoModel::newFood()
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGenX(field.getCurrentBeginX() + 1, field.getFullSizeX() - 1);
    std::uniform_int_distribution<> randGenY(field.getCurrentBeginY() + 1, field.getFullSizeY() - 1);
    int foodX = randGenX(generator);
    int foodY = randGenY(generator);

    while (field.getCell(foodX, foodY) != Field::Free){
        foodX = randGenX(generator);
        foodY = randGenY(generator);
    }
    field.setCell(foodX, foodY, Field::Food);
}


void SnakeEvoModel::death()
{
    isAlive = false;
    evolutionParameters.aliveSnakes--;
}


void SnakeEvoModel::deleteSnake()
{
	snakeBody* snakeTmp = nullptr;
	snakeBody* snakeSecondTmp = nullptr;

    if (snakeHeadTail){
        snakeTmp = snakeHeadTail->firstCell;
        while(snakeTmp)
        {
            snakeSecondTmp = snakeTmp;
            snakeTmp = snakeTmp->nextCell;
            delete snakeSecondTmp;
            snakeSecondTmp = nullptr;
        }
        snakeTmp = nullptr;
        delete snakeHeadTail;
        snakeHeadTail = nullptr;
    }
}
