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
	       	"Length of snakes",
	       	"Count of snakes",
	       	"Count of foods",

		    "Snake head color",
    		"Food color",
	    	"Snake body color one",
		    "Snake body color two",
	       	
    		"Back",
	    };

        std::string leftArrowString = " < ";
        std::string rightArrowString = " > ";
        std::string spaceString = "   ";
        const char *space = spaceString.c_str();
        const char *leftArrow = leftArrowString.c_str();
        
        enum settingsMenuChoicesConst 
	    {
                GameSpeed, SnakesLength, SnakesCount, FoodsCount, 
		SnakeHeadColor, FoodColor, SnakeBodyColorOne, SnakeBodyColorTwo,
		Back
	    };
        int firstMenuTitle = GameSpeed;
        int currentMenuTitle;
        int lastMenuTitle = Back;

        const char *rightArrow = rightArrowString.c_str();
        
        int currentParameter;
        
    public:
        void run() override;
        void menuFrame();
        void menuControllHandler();
        void menuControllSelect();

        void printParameter(int parameter);
        void printColor(int parameter);
        int getParameter(int count);
        void setParameter(int currentChoice, int side); 

};
#endif
