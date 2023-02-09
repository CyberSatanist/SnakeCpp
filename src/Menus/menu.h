#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "Screen/screen.h"

extern Screen currentScreen;

class Menu
{
    public:
        Menu() {};
        ~Menu() {};

    
    public:
        void run();


    protected:
        int currentChoice = 0;
        int menuChoiceCount = 0;
        bool menuOn = false;

        std::string menuTitle;
        std::vector<std::string> menuChoices;
        enum menuChoicesConst {}; 

        virtual void menuControllSelect(){};

        void menuControllHandler();
        void menuFrame();
        void setMenuChosenColor();
        void setMenuLineColor();
        void setMenuTitleColor();

};
#endif
