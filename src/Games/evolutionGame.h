#ifndef EVOLUTION_GAME_H
#define EVOLUTION_GAME_H
#include "../Models/Snake/snakeModel.h"
#include "../Models/Snake/snakeFoodModel.h"
#include "../Menus/snakePauseMenu.h"
#include "../Screen/screen.h"
#include "../Parameters/snakeParameters.h"
#include <string>

class EvolutionGame
{

    private:
        int foodX, foodY, snakeX, snakeY;

        Screen currentScreen;
        Screen::controll_keys key;
        Screen::controll_keys vector;
        EvolutionPauseMenu pauseMenu;

        SnakeParameters snakeParameters;

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
	EvolutionGame(Screen screen, SnakeParameters parameters);
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
