#ifndef EVOLUTION_H
#define EVOLUTION_H
#include <Screen/screen.h>
#include <Evolution/Bars/evoInfoBar.h>
#include <Evolution/Bars/evoToolsBar.h>
#include <Evolution/Models/snakeEvolutionModel.h>
#include <Evolution/Models/foodEvolutionModel.h>
#include <Evolution/Field/evoField.h>
extern Screen currentScreen;

class Evolution
{
    private:
        EvoField field;
        EvoInfoBar infoBar;
        EvoToolsBar toolsBar;

        int key;
        int foodX, foodY, snakeX, snakeY;

        void turn();
        void drawScreen();

        std::string deathText = "YOU ARE FINISHED";
        int deathTextColor = COLOR_RED;
        int deathTextBackground = COLOR_BLACK;

        struct foodList {
            FoodEvolutionModel currentFood;
            bool isFood;
            struct foodList *nextFood;
        };
        foodList* food = new foodList;
        foodList* foodTmp = new foodList;

        struct snakesList{
            EvoField currentEvoField;
            bool alive = true;
            SnakeEvolutionModel currentSnake;
            struct foodList *thisSnakesFood;
            struct snakesList *nextSnake;
        };
        snakesList* snakes = new snakesList;
        snakesList* snakeTmp = new snakesList;

        void checkFood();
        void checkDeath();
        void death();
        void drawSnakes();
        void drawFood();
        void eatFood(snakesList* snakes, foodList* food);

    public:
        Evolution();
	    void run();
};
#endif
