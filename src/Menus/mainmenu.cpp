#include "mainmenu.h"
#include "modeSelector.h"
#include "../Menus/settingsMenu.h"
#include "../Menus/controllsMenu.h"
#include "../Screen/screen.h"
        
ModeSelector modeSelector;
SettingsMenu settingsMenu;        
ControllsMenu controllsMenu;

void MainMenu::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::ModeSelectorChoice){
	    modeSelector.run();
    } else if (currentChoice == menuChoicesConst::Settings){
	    settingsMenu.run();
    } else if (currentChoice == menuChoicesConst::Controlls){
        controllsMenu.run();
    } else if (currentChoice == menuChoicesConst::Exit){
        menuOn = false;
    }
}
