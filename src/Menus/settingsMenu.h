#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "menu.h"
#include "SnakeGame/Menus/snakeSettingsMenu.h"
#include "Evolution/Menus/evoSettingsMenu.h"


class SettingsMenu : public Menu
{

    public:
        SettingsMenu();
        ~SettingsMenu() {};
    

    private:
        enum menuChoicesConst 
	    {
            SnakeGameSettignsChoice, 
            EvolutionSettingsChoice,
		    Back
	    };

		SnakeSettingsMenu snakeSettingsMenu;
		EvoSettingsMenu evoSettingsMenu;

        void menuControllSelect() override;

};
#endif
