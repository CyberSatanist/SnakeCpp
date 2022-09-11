#include "snakeGame.h"
#include "../Parameters/snakeParameters.h"
#include <unistd.h>

extern SnakeParameters snakeParameters;

SnakeGame::SnakeGame(Screen screen)
{
    Screen currentScreen;
    pauseMenu.initScreen(currentScreen);
}

void SnakeGame::run()
{
	SnakeModel newSnake;
	newSnake.init(currentScreen);
	snakes->currentSnake = newSnake;
	snakes->nextSnake = NULL;

	snakes->thisSnakesFood = foods;
        foodTmp = snakes->thisSnakesFood;
	for (int count = 0; count < snakeParameters.countOfFoods; count++)
	{
	    SnakeFoodModel newFood;
	    newFood.init(currentScreen);
	    foodTmp->currentFood = newFood;
	    foodTmp->isFood = true;
	    foodTmp->nextFood = new foodsList;
	    foodTmp = foodTmp->nextFood;
	    foodTmp->nextFood = NULL;
	}

	snakeParameters.snakeGameOn = true;
        while((key = currentScreen.controllHandler()) !=-1  & (snakeParameters.snakeGameOn)){
            turn();
	    checkFood();
	    drawFoods();
	    drawSnakes();
	    checkDeath();
	    timeout(snakeParameters.delayDuration);

            if (key == Screen::controll_keys::ESCAPE) {
                pauseMenu.run();
	        snakeParameters.snakeGameOn = pauseMenu.getGameOnBool();
            }
            vector = key;
            tmp = snakes;
            while(tmp->nextSnake){
                tmp->currentSnake.setVector(vector);
	        tmp = tmp->nextSnake;
            }
            tmp->currentSnake.setVector(vector);
        }
}

void SnakeGame::drawSnakes()
{
    tmp = snakes;
    while(tmp){
        tmp->currentSnake.drawSnake();
	tmp = tmp->nextSnake;
    }
}

void SnakeGame::turn()
{
    tmp = snakes;
    while(tmp->nextSnake){
        tmp->currentSnake.move();
        tmp = tmp->nextSnake;
    }
    tmp->currentSnake.move();

    currentScreen.endFrame();
    currentScreen.clearScreen();
}

void SnakeGame::checkFood()
{
    tmp = snakes;
    while(tmp){
        foodTmp = tmp->thisSnakesFood;
        while(foodTmp->nextFood){
            if (!foodTmp->isFood)
	    {
                foodTmp->currentFood.init(currentScreen);
                foodTmp->isFood = true;
	    } else {
		foodTmp->currentFood.getFoodCoordinates(&foodX, &foodY);
		tmp->currentSnake.getSnakeHeadCoordinates(&snakeX, &snakeY);
	        if (foodX == snakeX && foodY == snakeY) {
                    eatFood(tmp, foodTmp);
		}
	    }
	    foodTmp = foodTmp->nextFood;
        }
	tmp = tmp->nextSnake;
    }
}

void SnakeGame::drawFoods()
{
    tmp = snakes;
    while(tmp){
        foodTmp = tmp->thisSnakesFood;
        while(foodTmp->nextFood){
            foodTmp->currentFood.drawFood();
	    foodTmp = foodTmp->nextFood;
        }
	tmp = tmp->nextSnake;
    }
}

void SnakeGame::eatFood(snakesList* tmp, foodsList* tmpFoods)
{
    snakes->currentSnake.newCell();
    tmpFoods->isFood = false;
}


void SnakeGame::checkDeath()
{
    tmp = snakes;
    while(tmp->nextSnake){
        if (tmp->currentSnake.deathCheck()) {
            death();
	}
	tmp = tmp->nextSnake;
    }
    if(tmp->currentSnake.deathCheck()) {
        death();	    
    }
}

void SnakeGame::death()
{
    currentScreen.setCursor(currentScreen.getHight() / 2, (currentScreen.getWidth() / 2) - (deathText.length() / 2));
    currentScreen.setColor(deathTextColor, deathTextBackground);
    currentScreen.writeText(deathText.c_str());
    currentScreen.endFrame();
    snakeParameters.snakeGameOn = false;
    sleep(5);
    currentScreen.clearScreen();
}
