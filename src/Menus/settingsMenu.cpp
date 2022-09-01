#include "settingsMenu.h"
#include "../Screen/screen.h"
#include <string>
#include <array>
#include <charconv>
#include <iostream>
#include <sstream>


void SettingsMenu::run()
{
    currentScreen.clearScreen();
    settingsMenuOn = true;
    while (settingsMenuOn) {
	menuFrame();
	menuControllHandler();
    }
    currentScreen.clearScreen();
}

void SettingsMenu::initParameters(SnakeParameters* parameters)
{
    snakeParameters = *parameters;
}

void SettingsMenu::getParameters(SnakeParameters* parameters)
{
    *parameters = snakeParameters;
}

void SettingsMenu::menuFrame()
{

    snakeParameters.delayDuration;

    std::string delayString, lenghtString;
    std::string leftArrowString = " < ";
    std::string rightArrowString = " > ";
    std::string spaceString = "   ";

    delayString = std::to_string(snakeParameters.delayDuration);
    lenghtString = std::to_string(snakeParameters.snakeLenght);
    const char *delayDuration = delayString.c_str();
    const char *snakeLenght = lenghtString.c_str();
    const char *space = spaceString.c_str();
    const char *leftArrow = leftArrowString.c_str();
    const char *rightArrow = rightArrowString.c_str();

    for (int count = 0; count < ((settingsMenuChoiceCount-1)/2); count++) {
        currentScreen.setCursor(
            ((currentScreen.getHight() / ((settingsMenuChoiceCount/2) +2)) * (count+1)),
            (currentScreen.getWidth() / 6));
        if (currentChoice == count) {
            setMenuChosenColor();	
        } else {
            setMenuLineColor();
        }
        const char *strings = settingsMenuChoices[count].c_str();

	currentScreen.writeText(strings);
	switch (count){
            case 0:
            currentScreen.writeText(space);
            currentScreen.writeText(leftArrow);
	    currentScreen.writeText(delayDuration);
            currentScreen.writeText(rightArrow);
            break;
	    case 1:
            currentScreen.writeText(space);
            currentScreen.writeText(leftArrow);
	    currentScreen.writeText(snakeLenght);
            currentScreen.writeText(rightArrow);

	}
    }
    for (int count = ((settingsMenuChoiceCount)/2); count < (settingsMenuChoiceCount-1); count++) {
        currentScreen.setCursor(
            ((currentScreen.getHight() / ((settingsMenuChoiceCount/2) +2)) * (count+1 - ((settingsMenuChoiceCount)/2))),
            (currentScreen.getWidth() / 6) * 3);
	if (currentChoice == count) {
            setMenuChosenColor();	
        } else {
            setMenuLineColor();
        }
        const char *strings = settingsMenuChoices[count].c_str();
	currentScreen.writeText(strings);
    }
    if (currentChoice == settingsMenuChoiceCount-1) {
        setMenuChosenColor();	
    } else {
        setMenuLineColor();
    }
    currentScreen.setCursor(
            (currentScreen.getHight() / ((settingsMenuChoiceCount)/2) * ((settingsMenuChoiceCount/2)-1)),
            (currentScreen.getWidth() / 6) * 2);
        const char *strings = settingsMenuChoices[settingsMenuChoiceCount-1].c_str();
	currentScreen.writeText(strings);

    currentScreen.endFrame();
}

void SettingsMenu::menuControllHandler()
{
    switch(currentScreen.controllHandler()) {
	case currentScreen.controll_keys::UP: 
	    if (currentChoice == 0) {
		    currentChoice = settingsMenuChoiceCount - 1;
	    } else {
		    currentChoice--;
	    }
	    break;
	case currentScreen.controll_keys::DOWN: 
	    if (currentChoice == settingsMenuChoiceCount -1) {
		    currentChoice = 0;
	    } else {
		    currentChoice++;
	    }
	    break;
	case currentScreen.controll_keys::SELECT:
	    menuControllSelect();
	    break;
    }
}

void SettingsMenu::menuControllSelect()
{
    if (currentChoice == settingsMenuChoicesConst::GameSpeed){
	//snakePauseMenuOn = false;
    } else if (currentChoice == settingsMenuChoicesConst::Back){
	settingsMenuOn = false;
    }
}
