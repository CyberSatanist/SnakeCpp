#ifndef TOOLS_BAR_H
#define TOOLS_BAR_H
#include <Screen/screen.h>
#include <string>

extern Screen currentScreen;

class ToolsBar
{
    protected:
        int toolsBarXStart;
        int toolsBarYStart;
        int toolsBarXEnd;
        int toolsBarYEnd;

        bool toolsBarOn = false;

        int count;
        int rows;
        int columns;
        int currentColumn;
        int currentRow;
        int currentChoice = 0;
        int choicesCount;

        enum toolsBarChoicesConst {};

        int firstToolsBarTitle;
        int currentToolsBarTitle;
        int lastToolsBarTitle;
        int currentToolsParameter;

        virtual void menuControllSelect() {};
        virtual void writeString(int count) {};

    public:
        std::string barTitle;
        void initToolsBar(int xStart, int yStart, int xEnd, int yEnd);
        void drawToolsBar();
        void menuControllHandler(int key);
};

#endif