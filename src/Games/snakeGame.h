#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "../Models/Snake/snakeModel.h"
#include "../Models/Snake/snakeFoodModel.h"
#include "../Menus/snakePauseMenu.h"
#include "../Screen/screen.h"
#include "../Parameters/snakeParameters.h"
#include <string>

class SnakeGame
{

    private:
        int foodX, foodY, snakeX, snakeY;

        Screen currentScreen;
        Screen::controll_keys key;
        Screen::controll_keys vector;
        SnakePauseMenu pauseMenu;

        SnakeParameters snakeParameters;

        std::string deathText = "YOU ARE FINISHED";
        int deathTextColor = COLOR_RED;
        int deathTextBackground = COLOR_BLACK;


        struct foodsList {
            SnakeFoodModel currentFood;
            bool isFood;
            struct foodsList *nextFood;
        };
        foodsList* foods = new foodsList;
	foodsList* foodTmp = new foodsList;


        struct snakesList{
            SnakeModel currentSnake;
            struct foodsList *thisSnakesFood;
            struct snakesList *nextSnake;
        };
        snakesList* snakes = new snakesList;
        snakesList* tmp = new snakesList;

       
    public:
	SnakeGame(Screen screen, SnakeParameters parameters);
	void run();
	void turn();
	void checkFood();
	void checkDeath();
	void death();
	void drawSnakes();
	void drawFoods();
	void eatFood(snakesList* snakes, foodsList* foods);

};
#endif
