#ifndef EVO_TOOLS_BAR_H
#define EVO_TOOLS_BAR_H
#include <Bars/toolsBar.h>


class EvoToolsBar : public ToolsBar 
{
    private:

        static const int toolsBarChoiceCount = 6;
        std::string toolsBarChoices[toolsBarChoiceCount] = 
        {
            "Save current state",
            "Load state",
            "Speed up",
            "Speed down",
            "Pause",
            "Exit",
        };
        enum toolsBarChoicesConst {Save, Load, SpeedUp, SpeedDown, Pause, Exit};

        void menuControllSelect() override;
        void writeString(int count) override;

    public:
        bool pauseOn = false;
        EvoToolsBar(){
            this->barTitle = "~TOOLS~";

            this->choicesCount = toolsBarChoiceCount;
            this->rows = toolsBarChoiceCount / 3;
            this->columns = toolsBarChoiceCount / rows;

            this->firstToolsBarTitle = Save;
            this->lastToolsBarTitle = Exit;
        }

};

#endif