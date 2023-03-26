#include "snakeEvoModel.h"
#include "Evolution/NeuralNetwork/standartNetwork/standartNetwork.h"
#include "Evolution/NeuralNetwork/straightNetwork/straightNetwork.h"
#include "Evolution/NeuralNetwork/simpleNetwork/simpleNetwork.h"
#include "Evolution/Parameters/evolutionParameters.h"

extern EvolutionParameters evolutionParameters;

template <class Network>
SnakeEvoModel<Network>::SnakeEvoModel(int startX, int startY, int length, int color)
    : field(evolutionParameters.currentFieldSizeX, evolutionParameters.currentFieldSizeY, evolutionParameters.fullFieldSizeX, evolutionParameters.fullFieldSizeY)
{
    snakeId = evolutionParameters.snakeIdCounter;
    evolutionParameters.snakeIdCounter++;
}


template <class Network>
void SnakeEvoModel<Network>::init(Network *newNetwork, int startX, int startY, int length, int color)
{
    network = newNetwork;

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


template <class Network>
void SnakeEvoModel<Network>::drawField()
{
    field.drawField();
}


template <class Network>
void SnakeEvoModel<Network>::drawStuff()
{
    field.drawSnakeAndFood();
}


template <class Network>
void SnakeEvoModel<Network>::getSnakeHeadCoordinates(int* x, int* y)
{
    *x = snakeHeadTail->firstCell->cellX;
    *y = snakeHeadTail->firstCell->cellY;
}


template <class Network>
void SnakeEvoModel<Network>::newCell()
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


template <class Network>
void SnakeEvoModel<Network>::move()
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


template <class Network>
void SnakeEvoModel<Network>::validation()
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


template <class Network>
void SnakeEvoModel<Network>::setVector(int direction)
{
    direction = network->useMind(field, snakeHeadTail->firstCell->cellX, snakeHeadTail->firstCell->cellY);

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


template <class Network>
void SnakeEvoModel<Network>::initFood()
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


template <class Network>
void SnakeEvoModel<Network>::initBorders()
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


template <class Network>
void SnakeEvoModel<Network>::snakeEat()
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


template <class Network>
void SnakeEvoModel<Network>::newFood()
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


template <class Network>
void SnakeEvoModel<Network>::death()
{
    isAlive = false;
    evolutionParameters.aliveSnakes--;
}


template <class Network>
void SnakeEvoModel<Network>::deleteSnake()
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
    delete network;
}



template class SnakeEvoModel<StandartNetwork>;

template class SnakeEvoModel<StraightNetwork>;

template class SnakeEvoModel<SimpleNetwork>;
