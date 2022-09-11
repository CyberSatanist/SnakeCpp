#ifndef SNAKEPARAMETERS_H
#define SNAKEPARAMETERS_H

#include "../Screen/screen.h"

class SnakeParameters {

    public:
        bool snakeGameOn = false;

//SnakeGame
        int countOfFoods = 10;
        int countOfSnakes = 1;
        int snakeLength = 6;
        int delayDuration = 80;
        int whiteColor = COLOR_WHITE;

//SnakeModel
        int snakeHeadColor = COLOR_YELLOW;
        int snakeBodyColorOne = COLOR_GREEN;
        int snakeBodyColorTwo = COLOR_GREEN;

//FoodModel
        int foodColor = COLOR_RED;

};

#endif
