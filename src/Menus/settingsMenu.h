#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "menu.h"


class SettingsMenu : public Menu
{
    
    private:

        static const int menuChoiceCount = 3;

        std::string menuChoices[menuChoiceCount] = 
	    {
            "Snake Game settings",
	       	"Evolution settings",
    		"Back"
	    };

        enum menuChoicesConst 
	    {
            SnakeGameSettignsChoice, 
            EvolutionSettingsChoice,
		    Back
	    };

        void menuControllSelect() override;

    public:
        SettingsMenu() {
            this->menuConst = menuChoiceCount;
            this->menuTitle = "   ~S E T T I N G S  S E L E C T O R~   ";
        };
};
#endif
