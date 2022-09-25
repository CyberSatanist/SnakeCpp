#ifndef MODESELECTOR_H
#define MODESELECTOR_H

#include "menu.h"


class ModeSelector : public Menu
{
    
    private:

        static const int menuChoiceCount = 3;

        std::string menuChoices[menuChoiceCount] = 
	    {
            "Snake Game",
	       	"Evolution",
    		"Back"
	    };

        enum menuChoicesConst 
	    {
            SnakeGameChoice, 
            EvolutionChoice,
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
