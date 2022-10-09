#ifndef SNAKE_EVO_MODEL_H
#define SNAKE_EVO_MODEL_H

#include <Screen/screen.h>
#include <Evolution/Field/evoField.h>
#include <Evolution/NeuralNetwork/standartNetwork.h>
#include <Evolution/Models/foodEvoModel.h>

extern Screen currentScreen;

class SnakeEvoModel
{
    private:

		struct snakeBody{
	    	int cellX, cellY;
            struct snakeBody *nextCell;
            struct snakeBody *prevCell;
        };

		struct snakeLocs{
			struct snakeBody *firstCell;
			struct snakeBody *lastCell;
		};

		snakeBody* currentBody = new snakeBody;
		snakeBody* snakeTmp = new snakeBody;
		snakeLocs* snakeHeadTail = new snakeLocs;

        struct foodList {
            FoodEvoModel currentFood;
            struct foodList *nextFood;
        };
        foodList* food = new foodList;
        foodList* foodTmp = new foodList;

		void initFood();
		void initField();

    public:
		StandartNetwork network;

		bool isAlive = false;
        EvoField field;

        int vector = Screen::controll_keys::UP;
		int score = 0;
		int snakeId;
		
		void init(int startX, int startY, int length, int color);
		void deleteSnake();
		void newCell();
		void newFood();
		void move();
		void snakeEat();
		void getSnakeHeadCoordinates(int* x, int* y);

//Draw
		void drawField();
		void drawStuff();
		void drawSnake();
		void drawFood();

		void setVector(int direction);
		void validation();
		void death();
};
#endif
