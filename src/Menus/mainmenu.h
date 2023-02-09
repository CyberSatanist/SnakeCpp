#ifndef MAINMENU_H
#define MAINMENU_H

#include "modeSelector.h"
#include "Menus/settingsMenu.h"
#include "Menus/controllsMenu.h"

#include "menu.h"

class MainMenu : public Menu 
{
    public:
        MainMenu();
        ~MainMenu() {};

    private:
        ModeSelector modeSelector;
        SettingsMenu settingsMenu;        
        ControllsMenu controllsMenu;

        enum menuChoicesConst {ModeSelectorChoice, Settings, Controlls, Exit};

        void menuControllSelect() override;

};
#endif
