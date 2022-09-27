#ifndef LIFE_GAME_INFO_SUB_MENU_H
#define LIFE_GAME_INFO_SUB_MENU_H
#include "../../../../Screen/screen.h"
#include <string>

extern Screen currentScreen;

class LifeInfoSubMenu
{
    private:
        int infoBarXStart;
        int infoBarYStart;
        int infoBarXEnd;
        int infoBarYEnd;

        static const int infoMenuChoiceCount = 7;
        std::string infoMenuChoices[infoMenuChoiceCount] = 
        {
            "Turn",
            "Field Full Size X",
            "Field Full Size Y",
            "Current Starting X",
            "Current Starting Y",
            "Current Ending X",
            "Current Ending Y",
        };
        enum infoMenuChoicesConst {Turn, FieldX, FieldY, StartX, StartY, EndX, EndY};
        int firstInfoMenuTitle = Turn;
        int currentInfoMenuTitle;
        int lastInfoMenuTitle = EndY;
        int currentInfoParameter;

        int getParameter(int count);
        void printParameter(int parameter);

    public:
        void initInfoBar(int xStart, int yStart, int xEnd, int yEnd);
        void drawInfoBar();
};

#endif