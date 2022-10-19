#ifndef EVOLUTION_H
#define EVOLUTION_H
#include <Screen/screen.h>
#include <Evolution/Bars/evoInfoBar.h>
#include <Evolution/Bars/evoToolsBar.h>
#include <Evolution/Bars/evoSquareBar.h>
#include <Evolution/Models/snakeEvoModel.h>

extern Screen currentScreen;

class Evolution
{
    private:
        EvoField field;
        EvoInfoBar infoBar;
        EvoToolsBar toolsBar;
        EvoSquareBar squareBar;

        int key;
        int foodX, foodY, snakeX, snakeY;

        void turn();
        void drawScreen();
        void evolveSnakes();
        void getBest();

        std::string deathText = "YOU ARE FINISHED";
        int deathTextColor = COLOR_RED;
        int deathTextBackground = COLOR_BLACK;

        struct snakesList{
            SnakeEvoModel currentSnake;
            struct snakesList *nextSnake;
        };
        
        snakesList* snakes;
        snakesList* snakeTmp;
        snakesList* snakeSecondTmp;
        snakesList* snakeThirdTmp;
        snakesList* snakeFoursTmp;

        struct bestSnakesList{
            SnakeEvoModel currentSnake;
            struct bestSnakesList *nextSnake;
            struct bestSnakesList *prevSnake;
        };
        bestSnakesList* bestSnake;
        bestSnakesList* worstSnake;
        bestSnakesList* parentSnakes;
        bestSnakesList* snakeListTmp;
        bestSnakesList* snakeListSecondTmp;


        void initSnakes();
        void drawStuff();
        void deleteOldSnakes();

    public:
        Evolution();
	    void run();
};
#endif
