#include "evolution.h"
#include "Parameters/evolutionParameters.h"

extern EvolutionParameters evolutionParameters;

Evolution::Evolution()
{
    infoSubMenu.initInfoBar(
        0,
        currentScreen.getWidth() / evolutionParameters.fieldMaxY * evolutionParameters.fieldY + 1,
        currentScreen.getHight() / evolutionParameters.fieldMaxX * evolutionParameters.fieldX,
        currentScreen.getWidth()
    );

    toolsSubMenu.initToolsBar(
        currentScreen.getHight() / evolutionParameters.fieldMaxX * evolutionParameters.fieldX + 1, 
        0, 
        currentScreen.getHight(), 
        currentScreen.getWidth()
    );

    map.initMap(
        currentScreen.getHight() / evolutionParameters.fieldMaxX * evolutionParameters.fieldX,
        currentScreen.getWidth() / evolutionParameters.fieldMaxY * evolutionParameters.fieldY
    );

    timeout(evolutionParameters.delayDuration);
}


void Evolution::run()
{
    currentScreen.clearScreen();

    evolutionParameters.turn = 0;
    evolutionParameters.score = 0;

    SnakeEvolutionModel newSnake;
	newSnake.init((map.getSizeX() / 2), (map.getSizeX() / 2), evolutionParameters.snakeLength, evolutionParameters.snakeOneBodyColor);
	snakes->currentSnake = newSnake;
	snakes->nextSnake = NULL;

	snakes->thisSnakesFood = food;
    foodTmp = snakes->thisSnakesFood;

	for (int count = 0; count < evolutionParameters.countOfFood; count++)
	{
	    FoodEvolutionModel newFood;
	    newFood.init((map.getSizeX() - 2), (map.getSizeY() - 2), evolutionParameters.snakeOnefoodColor);
	    foodTmp->currentFood = newFood;
	    foodTmp->isFood = true;
	    foodTmp->nextFood = new foodList;
	    foodTmp = foodTmp->nextFood;
	    foodTmp->nextFood = NULL;
	}

	evolutionParameters.evolutionOn = true;

    while((key = currentScreen.controllHandler()) !=-1  & (evolutionParameters.evolutionOn)){
        turn();
        drawScreen();
        checkFood();
	    drawFood();
        drawSnakes();
        checkDeath();
        toolsSubMenu.menuControllHandler(key);

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
    map.drawField();
    infoSubMenu.drawInfoBar();
    toolsSubMenu.drawToolsBar();
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
                foodTmp->currentFood.init((map.getSizeX() - 2), (map.getSizeY() - 2), evolutionParameters.snakeOnefoodColor);
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