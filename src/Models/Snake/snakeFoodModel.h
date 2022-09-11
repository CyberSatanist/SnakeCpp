#ifndef SNAKE_FOOD_MODEL_H
#define SNAKE_FOOD_MODEL_H
#include "../../Screen/screen.h"
#include "../../Parameters/snakeParameters.h"

class SnakeFoodModel
{

    private:
        int foodX, foodY;
	Screen currentScreen;

    public:
	void getFoodCoordinates(int* x, int* y);
        void init(Screen screen);
        void drawFood();
};
#endif
