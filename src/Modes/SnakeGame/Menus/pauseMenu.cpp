#include "pauseMenu.h"
#include <Menus/controllsMenu.h>


bool PauseMenu::getGameOnBool()
{
    return snakeBool;
}


void PauseMenu::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::Continue){
    	menuOn = false;
    } else if (currentChoice == menuChoicesConst::Controlls){
	    ControllsMenu controllsMenu;
        controllsMenu.run();
    } else if (currentChoice == menuChoicesConst::MainMenu){
	    menuOn = false;
        snakeBool = false;
    }
}
