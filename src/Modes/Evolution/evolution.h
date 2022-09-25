#ifndef EVOLUTION_H
#define EVOLUTION_H
#include "../../Screen/screen.h"
#include "Menus/SubMenus/infoSubMenu.h"
#include "Menus/SubMenus/toolsSubMenu.h"
#include "Models/snakeEvolutionModel.h"
#include "Models/foodEvolutionModel.h"
#include "Field/map.h"

class Evolution
{
    private:
        Map map;
        Screen currentScreen;
        InfoSubMenu infoSubMenu;
        ToolsSubMenu toolsSubMenu;

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
            Map currentMap;
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
	    Evolution(Screen screen);
	    void run();
};
#endif
