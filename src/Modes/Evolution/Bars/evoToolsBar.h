#ifndef EVO_TOOLS_BAR_H
#define EVO_TOOLS_BAR_H
#include <Bars/toolsBar.h>


class EvoToolsBar : public ToolsBar 
{
    private:

        static const int toolsBarChoiceCount = 8;
        std::string toolsBarChoices[toolsBarChoiceCount] = 
        {
            "Save state",
            "Load state",
            "Speed up",
            "Speed down",
            "Switch map",
            "Placeholder",
            "Pause",
            "Exit",
        };
        enum toolsBarChoicesConst {Save, Load, SpeedUp, SpeedDown, SwitchMap, Placeholder, Pause, Exit};

        void menuControllSelect() override;
        void writeString(int count) override;

    public:
        bool pauseOn = false;
        EvoToolsBar(){
            this->barTitle = "~TOOLS~";

            this->choicesCount = toolsBarChoiceCount;
            this->rows = toolsBarChoiceCount / 4;
            this->columns = toolsBarChoiceCount / rows;

            this->firstToolsBarTitle = Save;
            this->lastToolsBarTitle = Exit;
        }

};

#endif