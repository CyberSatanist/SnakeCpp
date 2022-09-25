#include "settingsMenu.h"
#include "../Modes/SnakeGame/Menus/snakeSettingsMenu.h"
//#include "../Modes/Evolution/Menus/evolutionSettingsMenu.h"


void SettingsMenu::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::SnakeGameSettignsChoice){
		SnakeSettingsMenu snakeSettingsMenu;
        snakeSettingsMenu.initScreen(currentScreen);
	    snakeSettingsMenu.run();
    } else if (currentChoice == menuChoicesConst::EvolutionSettingsChoice){
		//EvolutionSettingsMenu evolutionSettingsMenu;
        //evolutionSettingsMenu.initScreen(currentScreen);
	    //evolutionSettingsMenu.run();
    } else if (currentChoice == menuChoicesConst::Back){
        menuOn = false;
    }
}
