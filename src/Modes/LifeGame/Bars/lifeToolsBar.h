#ifndef LIFE_TOOLS_BAR_H
#define LIFE_TOOLS_BAR_H
#include <Bars/toolsBar.h>


class LifeToolsBar : public ToolsBar
{

    private:

        static const int toolsBarChoiceCount = 8;
        std::string toolsBarChoices[toolsBarChoiceCount] = 
        {
            "Save current state",
            "Load state",
            "Move Left",
            "Move Right",
            "Move Up",
            "Move Down",
            "Pause",
            "Exit",
        };
        enum toolsBarChoicesConst {Save, Load, Left, Right, Up, Down, Pause, Exit};

        void menuControllSelect() override;
        void writeString(int count) override;

    public:
        LifeToolsBar(){
            this->barTitle = "~TOOLS~";

            this->choicesCount = toolsBarChoiceCount;
            this->rows = 2;
            this->columns = toolsBarChoiceCount / rows;

            this->firstToolsBarTitle = Save;
            this->lastToolsBarTitle = Exit;
        }
};

#endif