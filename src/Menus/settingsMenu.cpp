#include "settingsMenu.h"
#include <SnakeGame/Menus/snakeSettingsMenu.h>
#include <Evolution/Menus/evoSettingsMenu.h>


void SettingsMenu::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::SnakeGameSettignsChoice){
		SnakeSettingsMenu snakeSettingsMenu;
	    snakeSettingsMenu.run();
    } else if (currentChoice == menuChoicesConst::EvolutionSettingsChoice){
		EvoSettingsMenu evoSettingsMenu;
	    evoSettingsMenu.run();
    } else if (currentChoice == menuChoicesConst::Back){
        menuOn = false;
    }
}
