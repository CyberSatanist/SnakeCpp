#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include "Screen/screen.h"

extern Screen currentScreen;

class Settings
{
    protected:
        bool settingsOn = false;

        std::string leftArrowString = " < ";
        std::string rightArrowString = " > ";
        std::string spaceString = "   ";
        const char *space = spaceString.c_str();
        const char *leftArrow = leftArrowString.c_str();
        const char *rightArrow = rightArrowString.c_str();

        int currentChoice = 0;
        int menuConst;
        int buttonsConst;
        int columns;
        int rows;
        std::string menuTitle;

        int colorsFrom;

        int firstMenuTitle;
        int lastMenuTitle;
        int currentMenuTitle;
        int currentParameter;

        virtual void menuControllSelect() {};
        virtual void writeString(int count) {};
        virtual void writeButton(int count) {};
        virtual int getParameter(int count) { return 0; };
        virtual void setParameter(int currentChoice, int side) {};
        
        void menuFrame();
        void menuControllHandler();
        void printParameter(int parameter);
        void printColor(int parameter);

        void setMenuChosenColor();
        void setMenuLineColor();
        void setMenuTitleColor();

    public:
        void run();
};
#endif
