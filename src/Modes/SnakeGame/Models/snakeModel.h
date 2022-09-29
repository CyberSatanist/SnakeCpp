#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#include <Screen/screen.h>

extern Screen currentScreen;

class SnakeModel
{
    private:
        struct snakeBody{
	    	int cellX, cellY;
        	Screen::controll_keys vector = Screen::controll_keys::UP;
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
		void init(Screen screen);
		void getSnakeHeadCoordinates(int* x, int* y);
		void drawSnake();
		void newCell();
		void move();
		void setVector(Screen::controll_keys vector);
		void wallValidation(snakeBody* snakeTmp);
		bool deathCheck();
};
#endif
