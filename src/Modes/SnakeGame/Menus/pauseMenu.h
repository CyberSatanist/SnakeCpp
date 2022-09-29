#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <Menus/menu.h>

class PauseMenu : public Menu {
    
    private:
        static const int menuChoiceCount = 3;

        std::string menuChoices[menuChoiceCount] = 
        {
            "Continue",
            "Controlls",
            "Exit to Mode Selector" 
        };

        enum menuChoicesConst 
	    {
            Continue,
            Controlls,
            MainMenu
	    };

        bool snakeBool = true;
        
        void menuControllSelect() override;
    
    public:
        PauseMenu() {
            this->menuConst = this->menuChoiceCount;
            this->menuTitle = "   ~P A U S E  M E N U~   ";
        };
        bool getGameOnBool();

        
};
#endif
