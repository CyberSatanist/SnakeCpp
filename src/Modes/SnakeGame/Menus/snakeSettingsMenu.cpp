#include "snakeSettingsMenu.h"
#include <SnakeGame/Parameters/snakeParameters.h>

extern SnakeParameters snakeParameters;


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
    if (currentChoice == (menuConst + buttonsConst - 1)){
        settingsOn = false;
    }
}


void SnakeSettingsMenu::writeString(int count)
{
    const char *string = menuChoices[count].c_str();
    currentScreen.writeText(string);
}


void SnakeSettingsMenu::writeButton(int count)
{
    const char *string = buttonChoices[count].c_str();
    currentScreen.writeText(string);
}