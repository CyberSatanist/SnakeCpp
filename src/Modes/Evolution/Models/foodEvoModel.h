#ifndef FOOD_EVOLUTION_MODEL_H
#define FOOD_EVOLUTION_MODEL_H

#include <Screen/screen.h>
#include <random>

extern Screen currentScreen;

class FoodEvoModel
{
    private:
        int foodX, foodY, foodColor, thisFieldX, thisFieldY;

    public:
        void init(int fieldX, int fieldY, int color);
	    void getFoodData(int* x, int* y, int* color);
        void getFoodCoordinates(int* x, int* y);
        void drawFood();
        int randX();
        int randY();
        int cellX();
        int cellY();
};
#endif