#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <vector>
#include "Screen/screen.h"

extern Screen currentScreen;

class Settings
{
    public:
        Settings() {};
        ~Settings() {};

        void run();


    protected:
        bool settingsOn = false;

        const char *space = "   ";
        const char *leftArrow = " < ";
        const char *rightArrow = " > ";

        int currentChoice = 0;
        int columns = 0;
        int rows = 0;

        std::string menuTitle;
        std::vector<std::string> menuChoices;
        std::vector<std::string> buttonChoices;

        int colorsFrom = 0;
        int firstMenuTitle = 0;
        int lastMenuTitle = 0;

        virtual void menuControllSelect() {};
        virtual int getParameter(int count) { return 0; };
        virtual void setParameter(int currentChoice, int side) {};
        
        void menuFrame();
        void menuControllHandler();
        void printParameter(int parameter);
        void printColor(int parameter);
        void writeString(int count);
        void writeButton(int count);

        void setMenuChosenColor();
        void setMenuLineColor();
        void setMenuTitleColor();

};
#endif
