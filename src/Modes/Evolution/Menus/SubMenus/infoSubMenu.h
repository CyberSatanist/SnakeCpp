#ifndef EVOLUTION_INFO_SUB_MENU_H
#define EVOLUTION_INFO_SUB_MENU_H
#include "../../../../Screen/screen.h"
#include <string>

class InfoSubMenu
{
    private:
        Screen currentScreen;

        int infoBarXStart;
        int infoBarYStart;
        int infoBarXEnd;
        int infoBarYEnd;

        static const int infoMenuChoiceCount = 3;
        std::string infoMenuChoices[infoMenuChoiceCount] = 
        {
            "Generation",
            "Highest score",
            "Evolution time",
        };
        enum infoMenuChoicesConst {Generation, Score, Time};
        int firstInfoMenuTitle = Generation;
        int currentInfoMenuTitle;
        int lastInfoMenuTitle = Time;
        int currentInfoParameter;

        int getParameter(int count);
        void printParameter(int parameter);

    public:
        void initInfoBar(int xStart, int yStart, int xEnd, int yEnd);
        void drawInfoBar();
};

#endif