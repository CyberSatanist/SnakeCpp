#ifndef MENU_H
#define MENU_H

#include <string>
#include "../Screen/screen.h"

extern Screen currentScreen;

class Menu
{

    protected:
        int currentChoice = 0;
        int menuChoiceCount = 0;
        bool menuOn = false;

        int menuConst;
        std::string menuTitle;
        std::string menuChoices[0];
        enum menuChoicesConst {}; 

        virtual void menuControllSelect(){};

        void menuControllHandler();
        void menuFrame();
        void setMenuChosenColor();
        void setMenuLineColor();
        void setMenuTitleColor();

    public:
        void run();




};
#endif
