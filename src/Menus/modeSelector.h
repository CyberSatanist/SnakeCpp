#ifndef MODESELECTOR_H
#define MODESELECTOR_H

#include "menu.h"


class ModeSelector : public Menu
{
    public:
        ModeSelector();
        ~ModeSelector() {};


    private:

        enum menuChoicesConst 
	    {
            SnakeGameChoice, 
            EvolutionChoice,
            LifeGameChoice,
		    Back
	    };

        void menuControllSelect() override;
        
};
#endif
