#ifndef SNAKEPARAMETERS_H
#define SNAKEPARAMETERS_H

#include <Parameters/parameters.h>

class SnakeParameters : public Parameters
{

    public:

//SnakeGame
        int countOfFood = 10;
        int countOfSnakes = 1;
        int snakeLength = 6;
        int delayDuration = 80;

//SnakeModel
        int snakeHeadColor = COLOR_YELLOW;
        int snakeBodyColorOne = COLOR_GREEN;
        int snakeBodyColorTwo = COLOR_GREEN;

//FoodModel
        int foodColor = COLOR_RED;

};

#endif
