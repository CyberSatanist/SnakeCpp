#include "mainmenu.h"
#include "../Screen/screen.h"
#include "../Games/snakeGame.h"
#include "../Menus/settingsMenu.h"

void MainMenu::run()
{
    mainMenuOn = true;
    while (mainMenuOn) {

        //SnakeSettingMenu settingsMenu(snakeGame);
        //SnakeControllsMenu settingsMenu();
	
	menuFrame();
	menuControllHandler();
    
    }
}

void MainMenu::menuFrame()
{
    for (int count = 0; count < mainMenuChoiceCount; count++) {
        currentScreen.setCursor(
            ((currentScreen.getHight() / (mainMenuChoiceCount+1)) * (count+1)),
            (currentScreen.getWidth() / 2) - (mainMenuChoices[count].length())/2);
	if (currentChoice == count) {
            setMenuChosenColor();	
        } else {
            setMenuLineColor();
        }
        const char *strings = mainMenuChoices[count].c_str();
	currentScreen.writeText(strings);
	currentScreen.endFrame();
    }
}

void MainMenu::menuControllHandler()
{
    switch(currentScreen.controllHandler()) {
	case currentScreen.controll_keys::UP: 
	    if (currentChoice == 0) {
		    currentChoice = mainMenuChoiceCount - 1;
	    } else {
		    currentChoice--;
	    }
	    break;
	case currentScreen.controll_keys::DOWN: 
	    if (currentChoice == mainMenuChoiceCount -1) {
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

void MainMenu::menuControllSelect()
{
    if (currentChoice == mainMenuChoicesConst::New_game){
        SnakeGame snakeGame(currentScreen, parameters);
	snakeGame.run();
    } else if (currentChoice == mainMenuChoicesConst::Settings){
        SettingsMenu settingsMenu;
        settingsMenu.initParameters(&parameters);
	settingsMenu.run();
        settingsMenu.getParameters(&parameters);
    } else if (currentChoice == mainMenuChoicesConst::Controlls){
        mainMenuOn = false;
    } else if (currentChoice == mainMenuChoicesConst::Exit){
        mainMenuOn = false;
    }
}
