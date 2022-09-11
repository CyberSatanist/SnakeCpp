#include "snakePauseMenu.h"
#include "../Screen/screen.h"
#include "../Games/snakeGame.h"
#include "../Menus/controllsMenu.h"

void SnakePauseMenu::run()
{
    currentScreen.clearScreen();
    snakePauseMenuOn = true;
    snakeBool = true;
    while (snakePauseMenuOn) {

	SnakePauseMenu::menuFrame();
	SnakePauseMenu::menuControllHandler();
    }
    currentScreen.clearScreen();
}

bool SnakePauseMenu::getGameOnBool()
{
    return snakeBool;
}

void SnakePauseMenu::menuFrame()
{
    for (int count = 0; count < snakePauseMenuChoiceCount; count++) {
        currentScreen.setCursor(
            ((currentScreen.getHight() / (snakePauseMenuChoiceCount+1)) * (count+1)),
            (currentScreen.getWidth() / 2) - (snakePauseMenuChoices[count].length())/2);
	if (currentChoice == count) {
            setMenuChosenColor();	
        } else {
            setMenuLineColor();
        }
        const char *strings = snakePauseMenuChoices[count].c_str();
	currentScreen.writeText(strings);
	currentScreen.endFrame();
    }
}

void SnakePauseMenu::menuControllHandler()
{
    switch(currentScreen.controllHandler()) {
	case currentScreen.controll_keys::UP: 
	    if (currentChoice == 0) {
		    currentChoice = snakePauseMenuChoiceCount - 1;
	    } else {
		    currentChoice--;
	    }
	    break;
	case currentScreen.controll_keys::DOWN: 
	    if (currentChoice == snakePauseMenuChoiceCount -1) {
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

void SnakePauseMenu::menuControllSelect()
{
    if (currentChoice == snakePauseMenuChoicesConst::Continue){
    	snakePauseMenuOn = false;
    } else if (currentChoice == snakePauseMenuChoicesConst::Controlls){
	    ControllsMenu controllsMenu;
        controllsMenu.run();
    } else if (currentChoice == snakePauseMenuChoicesConst::MainMenu){
	    snakePauseMenuOn = false;
        snakeBool = false;
    }
}
