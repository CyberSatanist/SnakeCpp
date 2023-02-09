#ifndef SNAKE_EVO_MODEL_H
#define SNAKE_EVO_MODEL_H

#include <random>
#include "Screen/screen.h"
#include "Evolution/Field/evoField.h"
#include "NeuralNetwork/network.h"
#include "Evolution/NeuralNetwork/standartNetwork/standartNetwork.h"
#include "Evolution/NeuralNetwork/straightNetwork/straightNetwork.h"
#include "Evolution/NeuralNetwork/simpleNetwork/simpleNetwork.h"

extern Screen currentScreen;

class SnakeEvoModel
{
	public:
		SnakeEvoModel(int startX = 0, int startY = 0, int length = 0, int color = 0);
		~SnakeEvoModel() {};


    private:
		int score = 0;
		int snakeId = 0;
		bool isAlive = false;

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

		void newCell();
		void newFood();
		void snakeEat();

    public:
		//StandartNetwork network;
    	StraightNetwork network;
		//SimpleNetwork network;
        EvoField field;


        int vector = Screen::controll_keys::UP;
		int foodEaten = 0;
		int turnsLeft = evolutionParameters.turnsToDeath;
		
		void init(int startX, int startY, int length, int color);
		void deleteSnake();
		void move();
		void setVector(int direction);
		void validation();
		void death();
		inline void increaseScore() { score++; };

		//Getters
		inline int getId() const { return snakeId; };
		inline int getScore() const { return score; };
		inline bool getIsAlive() const { return isAlive; };
		inline Field& getField() { return field; };
		void getSnakeHeadCoordinates(int* x, int* y);

		//Setters
		inline void setIsDead() { isAlive = false; }; 

		//Draw
		void drawField();
		void drawStuff();
		void drawSnake();
		void drawFood();
};
#endif
