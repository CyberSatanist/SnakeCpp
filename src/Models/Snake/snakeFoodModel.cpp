#include "snakeFoodModel.h"
#include <random>

extern SnakeParameters snakeParameters;

void SnakeFoodModel::init(Screen screen)
{
    currentScreen = screen;
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distributionX(1, currentScreen.getHight());
    std::uniform_int_distribution<> distributionY(1, currentScreen.getWidth());
    foodX = distributionX(generator);
    foodY = distributionY(generator);
}


void SnakeFoodModel::drawFood()
{
    currentScreen.setCursor(foodX, foodY);
    currentScreen.setColor(snakeParameters.whiteColor, snakeParameters.foodColor);
    currentScreen.writeText(" ");
}


void SnakeFoodModel::getFoodCoordinates(int* x, int* y)
{

    *x = foodX; 
    *y = foodY; 

}
