#include "settingsMenu.h"
#include <array>
#include <charconv>
#include <iostream>
#include <sstream>
#include "../Modes/SnakeGame/Menus/snakeSettingsMenu.h"
//#include "../Modes/Evolution/Menus/evolutionSettingsMenu.h"
#include "../Modes/SnakeGame/Parameters/snakeParameters.h"
//#include "../Modes/Evolution/Parameters/evolutionParameters.h"


void SettingsMenu::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::SnakeGameSettignsChoice){
		SnakeSettingsMenu snakeSettingsMenu;
        snakeSettingsMenu.initScreen(currentScreen);
	    snakeSettingsMenu.run();
    } else if (currentChoice == menuChoicesConst::EvolutionSettingsChoice){
		//EvolutionSettingsMenu evolutionSettingsMenu;
       // evolutionSettingsMenu.initScreen(currentScreen);
	  //  evolutionSettingsMenu.run();
    } else if (currentChoice == menuChoicesConst::Back){
        menuOn = false;
    }
}
