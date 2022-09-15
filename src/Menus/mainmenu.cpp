#include "mainmenu.h"
#include "modeSelector.h"
#include "../Menus/settingsMenu.h"
#include "../Menus/controllsMenu.h"

SnakeParameters snakeParameters;
//EvolutionParameters evolutionParameters;


void MainMenu::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::ModeSelectorChoice){
		ModeSelector modeSelector;
		modeSelector.initScreen(currentScreen);
	    modeSelector.run();
    } else if (currentChoice == menuChoicesConst::Settings){
        SettingsMenu settingsMenu;
	    settingsMenu.run();
    } else if (currentChoice == menuChoicesConst::Controlls){
        ControllsMenu controllsMenu;
        controllsMenu.run();
    } else if (currentChoice == menuChoicesConst::Exit){
        menuOn = false;
    }
}
