#ifndef SNAKEPAUSEMENU_H
#define SNAKEPAUSEMENU_H

#include <string>
#include "menu.h"

class SnakePauseMenu : public Menu {
    
    private:
        static const int snakePauseMenuChoiceCount = 3;
        bool snakePauseMenuOn = false;
        bool snakeBool = true;
        std::string snakePauseMenuChoices[snakePauseMenuChoiceCount] = {"Continue",  "Controlls", "Exit to Main Menu" };
    
    public:
        void run() override;
        void menuFrame();
	bool getGameOnBool();
        void menuControllHandler();
        void menuControllSelect();
        enum snakePauseMenuChoicesConst {Continue, Controlls, MainMenu};
};
#endif
