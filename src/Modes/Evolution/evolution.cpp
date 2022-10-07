#include "evolution.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;

Evolution::Evolution()
{
    infoBar.initInfoBar(
        evolutionParameters.infoBarStartX,
        evolutionParameters.infoBarStartY,
        evolutionParameters.infoBarEndX,
        evolutionParameters.infoBarEndY
    );
    toolsBar.initToolsBar(
        evolutionParameters.toolsBarStartX,
        evolutionParameters.toolsBarStartY, 
        evolutionParameters.toolsBarEndX, 
        evolutionParameters.toolsBarEndY
    );
    squareBar.initSquareBar(
        evolutionParameters.squareBarStartX,
        evolutionParameters.squareBarStartY, 
        evolutionParameters.squareBarEndX, 
        evolutionParameters.squareBarEndY
    );
}


void Evolution::run()
{
    timeout(evolutionParameters.delayDuration);

    currentScreen.clearScreen();

    evolutionParameters.turn = 0;
    evolutionParameters.score = 0;
    evolutionParameters.snakeIdCounter = 1;

    initSnakes();

	evolutionParameters.gameOn = true;

    while(evolutionParameters.gameOn){
        key = currentScreen.controllHandler();

        if (!toolsBar.pauseOn){
            turn();
            evolutionParameters.turn++;
            snakeTmp = snakes;
            while(snakeTmp->nextSnake){
                if (snakeTmp->currentSnake.isAlive)
                {
                    snakeTmp->currentSnake.setVector(key);
                }
                snakeTmp = snakeTmp->nextSnake;
            }
        }

        drawScreen();
        drawStuff();
        toolsBar.menuControllHandler(key);
    }
    currentScreen.clearScreen();
}


void Evolution::turn()
{
    snakeTmp = snakes;
    while(snakeTmp->nextSnake){
        if (snakeTmp->currentSnake.isAlive)
        {
            snakeTmp->currentSnake.move();
        }
        snakeTmp = snakeTmp->nextSnake;
    }

    currentScreen.endFrame();
    currentScreen.clearScreen();
}


void Evolution::drawScreen()
{
    infoBar.drawInfoBar();
    toolsBar.drawToolsBar();
    squareBar.drawMap(snakes->currentSnake.field);

    snakeTmp = snakes;
    do {
        if (snakeTmp->currentSnake.isAlive){
            snakeTmp->currentSnake.drawField();
            break;
        }
        snakeTmp = snakeTmp->nextSnake;
    } while (snakeTmp->nextSnake);
}


void Evolution::drawStuff()
{
    snakeTmp = snakes;
    while(snakeTmp->nextSnake){
        if (snakeTmp->currentSnake.isAlive)
        { 
            snakeTmp->currentSnake.drawStuff();
        }
	    snakeTmp = snakeTmp->nextSnake;
   } 
}


void Evolution::initSnakes()
{
    snakeTmp = snakes;

    int counter = 1;
    for (int count = 0; count < evolutionParameters.countOfSnakes; count++)
	{
        SnakeEvoModel newSnake;
        if ((evolutionParameters.fullFieldSizeY / 2) + (count * 2) + counter > (evolutionParameters.fullFieldSizeY - 3)){
            counter = 1;
        }
        newSnake.init(
            evolutionParameters.fullFieldSizeX / 2,
            (evolutionParameters.fullFieldSizeY / 2) + (count * 2) + counter,
            evolutionParameters.snakeLength,
            evolutionParameters.snakeOneBodyColor
        );
        snakeTmp->currentSnake = newSnake;
        snakeTmp->nextSnake = new snakesList;
        snakeTmp = snakeTmp->nextSnake;
        snakeTmp->nextSnake = NULL;
    counter++;
    }
    squareBar.initField(snakes->currentSnake.field);
}