#ifndef SNAKESETTINGSMENU_H
#define SNAKESETTINGSMENU_H

#include "../../../Menus/settings.h"

class SnakeSettingsMenu : public Settings {
    
    private:
        static const int menuChoiceCount = 9;

        std::string menuChoices[menuChoiceCount] = 
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
          
        enum menuChoicesConst 
	    {
            GameSpeed, SnakesLength, SnakesCount, FoodsCount, 
		    SnakeHeadColor, FoodColor, SnakeBodyColorOne, SnakeBodyColorTwo,
		    Back
	    };

        int firstMenuTitle = GameSpeed;
        int currentMenuTitle;
        int lastMenuTitle = Back;
        int currentParameter;

        void menuFrame();
        void menuControllHandler();
        void menuControllSelect() override;

        void printParameter(int parameter);
        void printColor(int parameter);
        void setParameter(int currentChoice, int side); 
        int getParameter(int count);
            
    public:
        SnakeSettingsMenu() {
            this->menuConst = menuChoiceCount;
            this->menuTitle = "   ~S E T T I N G S  M E N U~   ";
        };
        void run();

};
#endif
