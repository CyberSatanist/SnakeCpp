#ifndef SNAKE_EVO_MODEL_H
#define SNAKE_EVO_MODEL_H

#include <Screen/screen.h>
#include <Evolution/Field/evoField.h>
#include <NeuralNetwork/network.h>
#include <Evolution/NeuralNetwork/standartNetwork/standartNetwork.h>
#include <Evolution/NeuralNetwork/straightNetwork/straightNetwork.h>
#include <random>

extern Screen currentScreen;

class SnakeEvoModel
{
    private:

		struct snakeBody{
	    	int cellX, cellY;
            struct snakeBody *nextCell;
            struct snakeBody *prevCell;
        };

		snakeBody* currentBody;
		snakeBody* snakeTmp;

		struct snakeLocs{
			struct snakeBody *firstCell;
			struct snakeBody *lastCell;
		};

		snakeLocs* snakeHeadTail;

		void initFood();
		void initBorders();
		void initField();

		void newCell();
		void newFood();
		void snakeEat();

    public:
		//StandartNetwork network;

		StraightNetwork network;

        EvoField field;

		bool isAlive = false;

        int vector = Screen::controll_keys::UP;
		int score = 0;
		int turnsLeft = evolutionParameters.turnsToDeath;
		int snakeId;
		int foodEaten = 0;
		
		void init(int startX, int startY, int length, int color);
		void deleteSnake();
		
		void move();
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
