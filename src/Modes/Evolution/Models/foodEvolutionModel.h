#ifndef FOOD_EVOLUTION_MODEL_H
#define FOOD_EVOLUTION_MODEL_H

#include "../../../Screen/screen.h"

extern Screen currentScreen;

class FoodEvolutionModel
{
    private:
        int foodX, foodY, foodColor;

    public:
        void init(int fieldX, int fieldY, int color);
	    void getFoodData(int* x, int* y, int* color);
        void getFoodCoordinates(int* x, int* y);
        void drawFood();
};
#endif
