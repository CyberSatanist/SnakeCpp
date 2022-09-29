#ifndef EVO_TOOLS_BAR_H
#define EVO_TOOLS_BAR_H
#include <Screen/screen.h>
#include <Bars/toolsBar.h>
#include <string>

extern Screen currentScreen;

class EvoToolsBar //: public ToolsBar 
{
    private:
        int toolsBarXStart;
        int toolsBarYStart;
        int toolsBarXEnd;
        int toolsBarYEnd;

        int count;
        int rows = 2;
        int currentColumn;
        int currentRow;
        int currentChoice = 0;
        static const int toolsMenuChoiceCount = 4;
        int columns = toolsMenuChoiceCount / rows;
        std::string toolsMenuChoices[toolsMenuChoiceCount] = 
        {
            "Save current state",
            "Load state",
            "Pause",
            "Exit",
        };
        enum toolsMenuChoicesConst {Save, Load, Pause, Exit};
        int firstToolsMenuTitle = Save;
        int currentToolsMenuTitle;
        int lastToolsMenuTitle = Exit;
        int currentToolsParameter;

        void menuControllSelect();

    public:
        void initToolsBar(int xStart, int yStart, int xEnd, int yEnd);
        void drawToolsBar();
        void menuControllHandler(int key);
};

#endif