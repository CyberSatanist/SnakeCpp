#include "settingsMenu.h"


SettingsMenu::SettingsMenu()
{
    menuTitle = "   ~S E T T I N G S  S E L E C T O R~   ";

    menuChoices = 
    {
        "Snake Game settings",
        "Evolution settings",
        "Back"
    };
}


void SettingsMenu::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::SnakeGameSettignsChoice){
	    snakeSettingsMenu.run();
    } else if (currentChoice == menuChoicesConst::EvolutionSettingsChoice){
	    evoSettingsMenu.run();
    } else if (currentChoice == menuChoicesConst::Back){
        menuOn = false;
    }
}
