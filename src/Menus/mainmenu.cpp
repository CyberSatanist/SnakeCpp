#include "mainmenu.h"
#include "Screen/screen.h"


MainMenu::MainMenu()
{
    menuTitle = "   ~M A I N   M E N U~   ";

    menuChoices = 
    {
        "Select Mode",
        "Settings",
        "Controlls",
        "Exit"
    };
}


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
