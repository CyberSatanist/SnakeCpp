#ifndef MAINMENU_H
#define MAINMENU_H

#include "menu.h"

class MainMenu : public Menu 
{
    private:
        
        static const int menuChoiceCount = 4;

        std::string menuChoices[menuChoiceCount] = 
        {
            "Select Mode",
            "Settings",
            "Controlls",
            "Exit"
        };

        enum menuChoicesConst {ModeSelectorChoice, Settings, Controlls, Exit};

        void menuControllSelect() override;

    public:
        MainMenu() {
            this->menuConst = this->menuChoiceCount;
            this->menuTitle = "   ~M A I N   M E N U~   ";
        };

 

        
};
#endif
