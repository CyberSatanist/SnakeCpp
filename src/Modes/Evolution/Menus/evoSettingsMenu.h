#ifndef EVO_SETTINGS_MENU_H
#define EVO_SETTINGS_MENU_H

#include "Menus/settings.h"

class EvoSettingsMenu : public Settings
{
    public:
        EvoSettingsMenu();
        ~EvoSettingsMenu() {};
    
    private:
        enum menuChoicesConst 
	    {
            GameSpeed, SnakesLength, SnakesCount, FoodsCount, LayersCount, NeuronsCount
	    };

        enum buttonChoicesConst 
	    {
		    Back
	    };

        void menuControllSelect() override;
        void setParameter(int currentChoice, int side) override;
        int getParameter(int count) override;

};
#endif
