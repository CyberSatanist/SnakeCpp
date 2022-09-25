#include "snakeSettingsMenu.h"
#include "../Parameters/snakeParameters.h"


extern SnakeParameters snakeParameters;

void SnakeSettingsMenu::run()
{
    currentScreen.clearScreen();
    menuOn = true;
    while (menuOn) {
        menuFrame();
        menuControllHandler();
    }
    currentScreen.clearScreen();
}


void SnakeSettingsMenu::menuFrame()
{
    for (
        int count = 0, currentMenuTitle = firstMenuTitle;
        count < ((menuConst-1)/2); 
        count++, currentMenuTitle++
    ) {
        currentScreen.setCursor(
            ((currentScreen.getHight() / ((menuConst/2) +2)) * (count+1)),
            (currentScreen.getWidth() / 6));
        if (currentChoice == count) {
            setMenuChosenColor();	
        } else {
            setMenuLineColor();
        }
        const char *string = menuChoices[count].c_str();

    	currentScreen.writeText(string);
        currentParameter = getParameter(currentMenuTitle);
        printParameter(currentParameter);
	}

    for (
        int count = ((menuConst)/2), currentMenuTitle = firstMenuTitle + count;
        count < (menuConst-1);
        count++, currentMenuTitle++
    ) {
        currentScreen.setCursor(
            ((currentScreen.getHight() / ((menuConst/2) +2)) * (count+1 - ((menuConst)/2))),
            (currentScreen.getWidth() / 6) * 3);
        if (currentChoice == count) {
            setMenuChosenColor();	
        } else {
            setMenuLineColor();
        }
        const char *string = menuChoices[count].c_str();
	    currentScreen.writeText(string);
        currentParameter = getParameter(currentMenuTitle);
        printColor(currentParameter);
    }
    if (currentChoice == menuConst-1) {
        setMenuChosenColor();	
    } else {
        setMenuLineColor();
    }
    currentScreen.setCursor(
        currentScreen.getHight() - menuConst,
        (currentScreen.getWidth() - menuChoices[menuConst-1].length()) / 2);
    const char *strings = menuChoices[menuConst-1].c_str();
	currentScreen.writeText(strings);

    currentScreen.endFrame();
}

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


void SnakeSettingsMenu::menuControllHandler()
{
    switch(currentScreen.controllHandler()) {
        case currentScreen.controll_keys::UP: 
            if (currentChoice == 0) {
                currentChoice = menuConst - 1;
            } else {
                currentChoice--;
            }
            break;
        case currentScreen.controll_keys::DOWN: 
            if (currentChoice == menuConst -1) {
                currentChoice = 0;
            } else {
                currentChoice++;
            }
            break;
        case currentScreen.controll_keys::LEFT:
            setParameter(currentChoice, currentScreen.controll_keys::LEFT);
            break;
        case currentScreen.controll_keys::RIGHT:
            setParameter(currentChoice, currentScreen.controll_keys::RIGHT);
            break;
        case currentScreen.controll_keys::SELECT:
            menuControllSelect();
            break;
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

void SnakeSettingsMenu::printParameter(int parameter)
{
    std::string parameterString;
    parameterString = std::to_string(parameter);
    const char *parameterChar = parameterString.c_str();

    currentScreen.writeText(space);
    currentScreen.writeText(leftArrow);
	currentScreen.writeText(parameterChar);
    currentScreen.writeText(rightArrow);
}

void SnakeSettingsMenu::printColor(int parameter)
{
    std::string parameterString;
    switch (parameter)
    {
        case COLOR_BLACK:
            parameterString = "Black";
            break;
        case COLOR_RED:
            parameterString = "Red";
            break;
        case COLOR_GREEN:
            parameterString = "Green";
            break;
        case COLOR_YELLOW:
            parameterString = "Yellow";
            break;
        case COLOR_BLUE:
            parameterString = "Blue";
            break;
        case COLOR_MAGENTA:
            parameterString = "Magenta";
            break;
        case COLOR_CYAN:
            parameterString = "Cyan";
            break;
        case COLOR_WHITE:
            parameterString = "White";
            break;

    }
    const char *parameterChar = parameterString.c_str();
    
    currentScreen.writeText(space);
    currentScreen.writeText(leftArrow);
	currentScreen.writeText(parameterChar);
    currentScreen.writeText(rightArrow);
}

void SnakeSettingsMenu::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::Back){
        menuOn = false;
    }
}
