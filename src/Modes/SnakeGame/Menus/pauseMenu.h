#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Menus/menu.h"

class PauseMenu : public Menu 
{
    public:
        PauseMenu();
        ~PauseMenu() {};    

        bool getGameOnBool();


    private:
        enum menuChoicesConst 
	    {
            Continue,
            Controlls,
            MainMenu
	    };

        bool snakeBool = true;
        
        void menuControllSelect() override;
        
};
#endif
