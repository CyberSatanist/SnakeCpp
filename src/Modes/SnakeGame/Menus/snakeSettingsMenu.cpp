#include "snakeSettingsMenu.h"
#include "SnakeGame/Parameters/snakeParameters.h"

extern SnakeParameters snakeParameters;


SnakeSettingsMenu::SnakeSettingsMenu()
{
    menuTitle = "   ~S E T T I N G S  M E N U~   ";
    
    menuChoices = 
    {
        "Game speed",
        "Length of snakes",
        "Count of snakes",
        "Count of foods",

        "Snake head color",
        "Food color",
        "Snake body color one",
        "Snake body color two",
    };

    buttonChoices = { "Back" };
    
    rows = (int) menuChoices.size() / 2;
    columns = (int) menuChoices.size() / rows;

    colorsFrom = 3;

    firstMenuTitle = GameSpeed;
    lastMenuTitle = SnakeBodyColorTwo;
};


void SnakeSettingsMenu::setParameter(int currentChoice, int side)
{
    if (side == Screen::controll_keys::LEFT){
        switch (currentChoice) {
            case GameSpeed:
                if (snakeParameters.delayDuration == 10){
                    snakeParameters.delayDuration = 200;
                } else {
                    snakeParameters.delayDuration -= 10;
                }
                break;
            case SnakesLength:
                if (snakeParameters.snakeLength == 1){
                    snakeParameters.snakeLength = 30;
                } else {
                    snakeParameters.snakeLength--;
                }
                break;
            case SnakesCount:
                if (snakeParameters.countOfSnakes == 1){
                    snakeParameters.countOfSnakes = 100;
                } else {
                    snakeParameters.countOfSnakes--;
                }
                break;
            case FoodsCount:
                if (snakeParameters.countOfFood == 1){
                    snakeParameters.countOfFood = 100;
                } else {
                    snakeParameters.countOfFood--;
                }
                break;
            case SnakeHeadColor:
                if (snakeParameters.snakeHeadColor == COLOR_BLACK){
                    snakeParameters.snakeHeadColor = COLOR_WHITE;
                } else {
                    snakeParameters.snakeHeadColor--;
                }
                break;
            case FoodColor:
                if (snakeParameters.foodColor == COLOR_BLACK){
                    snakeParameters.foodColor = COLOR_WHITE;
                } else {
                    snakeParameters.foodColor--;
                }
                break;
            case SnakeBodyColorOne:
                if (snakeParameters.snakeBodyColorOne == COLOR_BLACK){
                    snakeParameters.snakeBodyColorOne = COLOR_WHITE;
                } else {
                    snakeParameters.snakeBodyColorOne--;
                }
                break;
            case SnakeBodyColorTwo:
                if (snakeParameters.snakeBodyColorTwo == COLOR_BLACK){
                    snakeParameters.snakeBodyColorTwo = COLOR_WHITE;
                } else {
                    snakeParameters.snakeBodyColorTwo--;
                }
                break;
        }
    } else if (side == Screen::controll_keys::RIGHT){
        switch (currentChoice) {
            case GameSpeed:
                if (snakeParameters.delayDuration == 200){
                    snakeParameters.delayDuration = 10;
                } else {
                    snakeParameters.delayDuration += 10;
                }
                break;
            case SnakesLength:
                if (snakeParameters.snakeLength == 30){
                    snakeParameters.snakeLength = 1;
                } else {
                    snakeParameters.snakeLength++;
                }
                break;
            case SnakesCount:
                if (snakeParameters.countOfSnakes == 100){
                    snakeParameters.countOfSnakes = 1;
                } else {
                    snakeParameters.countOfSnakes++;
                }
                break;
            case FoodsCount:
                if (snakeParameters.countOfFood == 100){
                    snakeParameters.countOfFood = 1;
                } else {
                    snakeParameters.countOfFood++;
                }
                break;
            case SnakeHeadColor:
                if (snakeParameters.snakeHeadColor == COLOR_WHITE){
                    snakeParameters.snakeHeadColor = COLOR_BLACK;
                } else {
                    snakeParameters.snakeHeadColor++;
                }
                break;
            case FoodColor:
                if (snakeParameters.foodColor == COLOR_WHITE){
                    snakeParameters.foodColor = COLOR_BLACK;
                } else {
                    snakeParameters.foodColor++;
                }
                break;
            case SnakeBodyColorOne:
                if (snakeParameters.snakeBodyColorOne == COLOR_WHITE){
                    snakeParameters.snakeBodyColorOne = COLOR_BLACK;
                } else {
                    snakeParameters.snakeBodyColorOne++;
                }
                break;
            case SnakeBodyColorTwo:
                if (snakeParameters.snakeBodyColorTwo == COLOR_WHITE){
                    snakeParameters.snakeBodyColorTwo = COLOR_BLACK;
                } else {
                    snakeParameters.snakeBodyColorTwo++;
                }
                break;
        }
    }
}


int SnakeSettingsMenu::getParameter(int count)
{
    switch(count) {
        case GameSpeed:
            return snakeParameters.delayDuration;
            break;
        case SnakesLength:
            return snakeParameters.snakeLength;
            break;
        case SnakesCount:
            return snakeParameters.countOfSnakes;
            break;
        case FoodsCount:
            return snakeParameters.countOfFood;
            break;
        case SnakeHeadColor:
            return snakeParameters.snakeHeadColor;
            break;
        case FoodColor:
            return snakeParameters.foodColor;
            break;
        case SnakeBodyColorOne:
            return snakeParameters.snakeBodyColorOne;
            break;
        case SnakeBodyColorTwo:
            return snakeParameters.snakeBodyColorTwo;
            break;
        default:
            return 0;
    }
}


void SnakeSettingsMenu::menuControllSelect()
{
    if (currentChoice == ((int) menuChoices.size() + (int) buttonChoices.size() - 1)){
        settingsOn = false;
    }
}