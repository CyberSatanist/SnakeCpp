#ifndef SNAKE_SETTINGS_MENU_H
#define SNAKE_SETTINGS_MENU_H

#include "Menus/settings.h"

class SnakeSettingsMenu : public Settings
{
	public:
		SnakeSettingsMenu();
		~SnakeSettingsMenu() {};


    private:

        enum menuChoicesConst 
	    {
            GameSpeed, SnakesLength, SnakesCount, FoodsCount, 
		    SnakeHeadColor, FoodColor, SnakeBodyColorOne, SnakeBodyColorTwo,
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
