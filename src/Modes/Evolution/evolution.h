#ifndef EVOLUTION_H
#define EVOLUTION_H
#include "../../Screen/screen.h"
#include "Field/map.h"
#include <string>

class Evolution
{
    private:
        Screen currentScreen;
        int key;
        Map map;

        int infoBarXStart;
        int infoBarYStart;
        int infoBarXEnd;
        int infoBarYEnd;

        int toolBarXStart;
        int toolBarYStart;
        int toolBarXEnd;
        int toolBarYEnd;

        int generation = 0;
        int score = 0;
        int time = 0;
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

        void turn();
        void drawScreen();
        void drawField();
        void drawInfoBar();
        void drawToolsBar();
        int getParameter(int count);
        void printParameter(int parameter);
        void menuControllHandler();
        void menuControllSelect();
       
    public:
	    Evolution(Screen screen);
	    void run();
};
#endif
