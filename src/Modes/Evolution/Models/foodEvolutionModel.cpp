#include "foodEvolutionModel.h"
#include "../Parameters/evolutionParameters.h"
#include <random>

extern EvolutionParameters evolutionParameters;

void FoodEvolutionModel::init(int fieldX, int fieldY, int color)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distributionX(2, fieldX);
    std::uniform_int_distribution<> distributionY(2, fieldY);
    foodX = distributionX(generator);
    foodY = distributionY(generator);
    foodColor = color;
}


void FoodEvolutionModel::getFoodData(int* x, int* y, int* color)
{
    *x = foodX;
    *y = foodY;
    *color = foodColor;
}


void FoodEvolutionModel::getFoodCoordinates(int* x, int* y)
{
    *x = foodX; 
    *y = foodY; 
}

void FoodEvolutionModel::drawFood()
{
    currentScreen.setCursor(foodX, foodY);
    currentScreen.setColor(foodColor, foodColor);
    currentScreen.writeText(" ");
}
