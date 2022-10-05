#ifndef SNAKE_SETTINGS_MENU_H
#define SNAKE_SETTINGS_MENU_H

#include <Menus/settings.h>

class SnakeSettingsMenu : public Settings {
    
    private:
        static const int menuChoiceCount = 8;

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
	    };

        enum menuChoicesConst 
	    {
            GameSpeed, SnakesLength, SnakesCount, FoodsCount, 
		    SnakeHeadColor, FoodColor, SnakeBodyColorOne, SnakeBodyColorTwo,
	    };

        static const int buttonChoiceCount = 1;
        
        std::string buttonChoices[buttonChoiceCount] = 
	    {
            "Back",
	    };

        enum buttonChoicesConst 
	    {
		    Back
	    };


        void menuControllSelect() override;
        void writeString(int count) override;
        void writeButton(int count) override;
        void setParameter(int currentChoice, int side) override;
        int getParameter(int count) override;
            
    public:
        SnakeSettingsMenu() {
            this->menuConst = menuChoiceCount;
            this->buttonsConst = buttonChoiceCount;
            this->menuTitle = "   ~S E T T I N G S  M E N U~   ";

            this->rows = menuChoiceCount / 2;
            this->columns = menuChoiceCount / rows;


            this->colorsFrom = 3;

            this->firstMenuTitle = GameSpeed;
            this->lastMenuTitle = SnakeBodyColorTwo;
        };

};
#endif
