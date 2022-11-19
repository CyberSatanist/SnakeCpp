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
	    	int cellX = 0;
			int cellY = 0;
            struct snakeBody *nextCell = nullptr;
            struct snakeBody *prevCell = nullptr;
        };
		snakeBody* currentBody	= nullptr;

		struct snakeLocs{
			struct snakeBody *firstCell = nullptr;
			struct snakeBody *lastCell = nullptr;
		};
		snakeLocs* snakeHeadTail = nullptr;

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
		int snakeId = 0;
		int foodEaten = 0;
		int turnsLeft = evolutionParameters.turnsToDeath;
		
		void init(int startX, int startY, int length, int color);
		void deleteSnake();
		void move();
		void getSnakeHeadCoordinates(int* x, int* y);
		void setVector(int direction);
		void validation();
		void death();

//Draw
		void drawField();
		void drawStuff();
		void drawSnake();
		void drawFood();
};
#endif
