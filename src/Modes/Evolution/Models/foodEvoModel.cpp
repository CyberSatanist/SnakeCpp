#include "foodEvoModel.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;

void FoodEvoModel::init(int fieldX, int fieldY, int color)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distributionX(2, fieldX);
    std::uniform_int_distribution<> distributionY(2, fieldY);
    thisFieldX = fieldX;
    thisFieldY = fieldY; 
    foodX = distributionX(generator);
    foodY = distributionY(generator);
    foodColor = color;
}


void FoodEvoModel::getFoodData(int* x, int* y, int* color)
{
    *x = foodX;
    *y = foodY;
    *color = foodColor;
}


void FoodEvoModel::getFoodCoordinates(int* x, int* y)
{
    *x = foodX; 
    *y = foodY; 
}

void FoodEvoModel::drawFood()
{
    currentScreen.setCursor(foodX, foodY);
    currentScreen.setColor(foodColor, foodColor);
    currentScreen.writeText(" ");
}

int FoodEvoModel::cellX()
{
    return foodX;
}


int FoodEvoModel::cellY()
{
    return foodY;
}

int FoodEvoModel::randX()
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distributionX(2, thisFieldX);
    int x = distributionX(generator);
    return x;
}


int FoodEvoModel::randY()
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distributionY(2, thisFieldY);
    int y = distributionY(generator);
    return y;
}
