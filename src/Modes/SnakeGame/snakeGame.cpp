#include "snakeGame.h"
#include <SnakeGame/Parameters/snakeParameters.h>
#include <unistd.h>

extern SnakeParameters snakeParameters;

void SnakeGame::run()
{
    currentScreen.endFrame();
    currentScreen.clearScreen();
    
	SnakeModel newSnake;
	newSnake.init(currentScreen);
	snakes->currentSnake = newSnake;
	snakes->nextSnake = NULL;

	snakes->thisSnakesFood = food;
    foodTmp = snakes->thisSnakesFood;

	for (int count = 0; count < snakeParameters.countOfFood; count++)
	{
	    FoodModel newFood;
	    newFood.init(currentScreen);
	    foodTmp->currentFood = newFood;
	    foodTmp->isFood = true;
	    foodTmp->nextFood = new foodList;
	    foodTmp = foodTmp->nextFood;
	    foodTmp->nextFood = NULL;
	}

	snakeParameters.gameOn = true;

    while(snakeParameters.gameOn){
        key = currentScreen.controllHandler();
        turn();
	    checkFood();
	    drawFood();
	    drawSnakes();
	    checkDeath();
	    timeout(snakeParameters.delayDuration);

        if (key == Screen::controll_keys::ESCAPE) {
            pauseMenu.run();
            snakeParameters.gameOn = pauseMenu.getGameOnBool();
        }
        vector = key;
        snakeTmp = snakes;
        while(snakeTmp->nextSnake){
            snakeTmp->currentSnake.setVector(vector);
            snakeTmp = snakeTmp->nextSnake;
        }
        snakeTmp->currentSnake.setVector(vector);
    }
}

void SnakeGame::drawSnakes()
{
    snakeTmp = snakes;
    while(snakeTmp){
        snakeTmp->currentSnake.drawSnake();
	    snakeTmp = snakeTmp->nextSnake;
    }
}

void SnakeGame::turn()
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

void SnakeGame::checkFood()
{
    snakeTmp = snakes;
    while(snakeTmp) {
        foodTmp = snakeTmp->thisSnakesFood;
        while(foodTmp->nextFood) {
            if (!foodTmp->isFood) {
                foodTmp->currentFood.init(currentScreen);
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

void SnakeGame::drawFood()
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

void SnakeGame::eatFood(snakesList* snakeTmp, foodList* foodTmp)
{
    snakes->currentSnake.newCell();
    foodTmp->isFood = false;
}


void SnakeGame::checkDeath()
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

void SnakeGame::death()
{
    currentScreen.setCursor(currentScreen.getHight() / 2, (currentScreen.getWidth() / 2) - (deathText.length() / 2));
    currentScreen.setColor(deathTextColor, deathTextBackground);
    currentScreen.writeText(deathText.c_str());
    currentScreen.endFrame();
    snakeParameters.gameOn = false;
    sleep(5);
    currentScreen.clearScreen();
}
