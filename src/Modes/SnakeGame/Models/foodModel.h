#ifndef FOOD_MODEL_H
#define FOOD_MODEL_H

#include <Screen/screen.h>

extern Screen currentScreen;

class FoodModel
{
    private:
        int foodX, foodY;
        
    public:
	    void getFoodCoordinates(int* x, int* y);
        void init(Screen screen);
        void drawFood();
};
#endif
