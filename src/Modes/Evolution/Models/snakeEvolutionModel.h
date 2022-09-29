#ifndef SNAKE_EVOLUTION_MODEL_H
#define SNAKE_EVOLUTION_MODEL_H

#include <Screen/screen.h>

extern Screen currentScreen;

class SnakeEvolutionModel
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

    public:
        int vector = Screen::controll_keys::UP;
		
		void init(int startX, int startY, int length, int color);
		void deleteSnake();
		void newCell();
		void move();
		void getSnakeHeadCoordinates(int* x, int* y);
		void drawSnake();
		void setVector(int direction);
		void validation(snakeBody* snakeTmp);
		bool deathCheck();
};
#endif
