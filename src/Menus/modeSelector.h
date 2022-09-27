#ifndef MODESELECTOR_H
#define MODESELECTOR_H

#include "menu.h"


class ModeSelector : public Menu
{
    
    private:

        static const int menuChoiceCount = 4;

        std::string menuChoices[menuChoiceCount] = 
	    {
            "Snake Game",
	       	"Evolution",
            "Life Game",
    		"Back"
	    };

        enum menuChoicesConst 
	    {
            SnakeGameChoice, 
            EvolutionChoice,
            LifeGameChoice,
		    Back
	    };

        void menuControllSelect() override;

    public:
        ModeSelector() {
            this->menuConst = menuChoiceCount;
            this->menuTitle = "   ~M O D E  S E L E C T O R~   ";
        };
};
#endif
