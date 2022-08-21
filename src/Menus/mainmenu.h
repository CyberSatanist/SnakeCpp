#ifndef MAINMENU_H
#define MAINEMENU_H

#include <string>
#include "menu.h"
#include "../Parameters/snakeParameters.h"

class MainMenu : public Menu {
    
    private:
        static const int mainMenuChoiceCount = 4;
        bool mainMenuOn = false;
        std::string mainMenuChoices[mainMenuChoiceCount] = {"New game", "Settings", "Controlls", "Exit"};
	SnakeParameters parameters;
    
    public:
        void run() override;
        void menuFrame();
        void menuControllHandler();
        void menuControllSelect();
        enum mainMenuChoicesConst {New_game, Settings, Controlls, Exit};
};
#endif
