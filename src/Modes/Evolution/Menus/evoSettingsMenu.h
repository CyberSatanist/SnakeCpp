#ifndef EVO_SETTINGS_MENU_H
#define EVO_SETTINGS_MENU_H

#include <Menus/settings.h>

class EvoSettingsMenu : public Settings {
    
    private:
        static const int menuChoiceCount = 6;

        std::string menuChoices[menuChoiceCount] = 
	    {
            "Game speed",
	       	"Length of snakes",
	       	"Count of snakes",
	       	"Count of foods",
            "Count of Neural Layers",
            "Count of Neurons in Layer"
	    };

        enum menuChoicesConst 
	    {
            GameSpeed, SnakesLength, SnakesCount, FoodsCount, LayersCount, NeuronsCount
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
        EvoSettingsMenu() {
            this->menuConst = menuChoiceCount;
            this->buttonsConst = buttonChoiceCount;
            this->menuTitle = "   ~E V O  S E T T I N G S  M E N U~   ";

            this->rows = menuChoiceCount / 2;
            this->columns = menuChoiceCount / rows;


            this->colorsFrom = 5;

            this->firstMenuTitle = GameSpeed;
            this->lastMenuTitle = NeuronsCount;
        };

};
#endif
