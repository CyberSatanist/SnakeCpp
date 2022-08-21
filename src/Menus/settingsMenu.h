#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <string>
#include "menu.h"
#include "../Parameters/snakeParameters.h"

class SettingsMenu : public Menu {
    
    private:
        static const int settingsMenuChoiceCount = 9;
        bool settingsMenuOn = false;
        std::string settingsMenuChoices[settingsMenuChoiceCount] = 
	    {
                "Game speed",
	       	"Lenght of snakes",
	       	"Count of snakes",
	       	"Count of foods",

		"Snake head color",
		"Food color",
		"Snake body color one",
		"Snake body color two",
	       	
		"Back",
	    };

	SnakeParameters snakeParameters;
    
    public:
        void run() override;
        void initParameters(SnakeParameters* parameters);
        void getParameters(SnakeParameters* parameters);
        void menuFrame();
        void menuControllHandler();
        void menuControllSelect();
        enum settingsMenuChoicesConst 
	    {
                GameSpeed, SnakesLenght, SnakesCount, FoodsCount, 
		SnakeHeadColor, FoodColor, SnakeBodyColorOne, SnakeBodyColorTwo,
		Back
	    };
};
#endif
