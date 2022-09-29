#include "settingsMenu.h"
#include <SnakeGame/Menus/snakeSettingsMenu.h>
//#include "Evolution/Menus/evolutionSettingsMenu.h"


void SettingsMenu::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::SnakeGameSettignsChoice){
		SnakeSettingsMenu snakeSettingsMenu;
	    snakeSettingsMenu.run();
    } else if (currentChoice == menuChoicesConst::EvolutionSettingsChoice){
		//EvolutionSettingsMenu evolutionSettingsMenu;
        //evolutionSettingsMenu.initScreen(currentScreen);
	    //evolutionSettingsMenu.run();
    } else if (currentChoice == menuChoicesConst::Back){
        menuOn = false;
    }
}
