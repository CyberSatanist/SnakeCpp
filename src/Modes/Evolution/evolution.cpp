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
    field.initField(
        evolutionParameters.currentFieldSizeX,
        evolutionParameters.currentFieldSizeY,
        evolutionParameters.fullFieldSizeX,
        evolutionParameters.fullFieldSizeY
    );
    field.initEvoField();
    
}


void Evolution::run()
{
    timeout(evolutionParameters.delayDuration);

    currentScreen.clearScreen();

    evolutionParameters.turn = 0;
    evolutionParameters.score = 0;

    SnakeEvolutionModel newSnake;
	newSnake.init((field.getFullSizeX() / 2), (field.getFullSizeY() / 2), evolutionParameters.snakeLength, evolutionParameters.snakeOneBodyColor);
	snakes->currentSnake = newSnake;
	snakes->nextSnake = NULL;

	snakes->thisSnakesFood = food;
    foodTmp = snakes->thisSnakesFood;

	for (int count = 0; count < evolutionParameters.countOfFood; count++)
	{
	    FoodEvolutionModel newFood;
	    newFood.init((field.getFullSizeX() - 2), (field.getFullSizeY() - 2), evolutionParameters.snakeOnefoodColor);
	    foodTmp->currentFood = newFood;
	    foodTmp->isFood = true;
	    foodTmp->nextFood = new foodList;
	    foodTmp = foodTmp->nextFood;
	    foodTmp->nextFood = NULL;
	}

	evolutionParameters.gameOn = true;

    while((key = currentScreen.controllHandler()) !=-1  & (evolutionParameters.gameOn)){
        turn();
        drawScreen();
        checkFood();
	    drawFood();
        drawSnakes();
        checkDeath();
        toolsBar.menuControllHandler(key);

        snakeTmp = snakes;
        while(snakeTmp->nextSnake){
            snakeTmp->currentSnake.setVector(key);
            snakeTmp = snakeTmp->nextSnake;
        }
        snakeTmp->currentSnake.setVector(key);

        evolutionParameters.turn++;
    }
    currentScreen.clearScreen();
}


void Evolution::turn()
{
    snakeTmp = snakes;
    while(snakeTmp->nextSnake){
        snakeTmp->currentSnake.move();
        snakeTmp = snakeTmp->nextSnake;
    }
    snakeTmp->currentSnake.move();

    currentScreen.endFrame();
    currentScreen.clearScreen();
}


void Evolution::drawScreen()
{
    field.drawField();
    infoBar.drawInfoBar();
    toolsBar.drawToolsBar();
    currentScreen.endFrame();
}

void Evolution::drawSnakes()
{
    snakeTmp = snakes;
    while(snakeTmp){
        snakeTmp->currentSnake.drawSnake();
	    snakeTmp = snakeTmp->nextSnake;
    }
}


void Evolution::checkFood()
{
    snakeTmp = snakes;
    while(snakeTmp) {
        foodTmp = snakeTmp->thisSnakesFood;
        while(foodTmp->nextFood) {
            if (!foodTmp->isFood) {
                foodTmp->currentFood.init((field.getFullSizeX() - 2), (field.getFullSizeY() - 2), evolutionParameters.snakeOnefoodColor);
                foodTmp->isFood = true;
            } else {
                foodTmp->currentFood.getFoodCoordinates(&foodX, &foodY);
                snakeTmp->currentSnake.getSnakeHeadCoordinates(&snakeX, &snakeY);
                if (foodX == snakeX && foodY == snakeY) {
                    eatFood(snakeTmp, foodTmp);
                }
	        }
	        foodTmp = foodTmp->nextFood;
        }
	    snakeTmp = snakeTmp->nextSnake;
    }
}

void Evolution::drawFood()
{
    snakeTmp = snakes;
    while(snakeTmp){
        foodTmp = snakeTmp->thisSnakesFood;
        while(foodTmp->nextFood){
            foodTmp->currentFood.drawFood();
	    foodTmp = foodTmp->nextFood;
        }
	    snakeTmp = snakeTmp->nextSnake;
    }
}

void Evolution::eatFood(snakesList* snakeTmp, foodList* foodTmp)
{
    snakes->currentSnake.newCell();
    foodTmp->isFood = false;
    evolutionParameters.score++;
}


void Evolution::checkDeath()
{
    snakeTmp = snakes;
    while(snakeTmp->nextSnake){
        if (snakeTmp->currentSnake.deathCheck()) {
            death();
	    }
        snakeTmp = snakeTmp->nextSnake;
    }
    if(snakeTmp->currentSnake.deathCheck()) {
        death();	    
    }
}

void Evolution::death()
{

}