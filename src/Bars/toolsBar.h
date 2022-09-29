#ifndef EVOLUTION_TOOLS_SUB_MENU_H
#define EVOLUTION_TOOLS_SUB_MENU_H
#include <Screen/screen.h>
#include <string>

extern Screen currentScreen;

class ToolsSubMenu
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