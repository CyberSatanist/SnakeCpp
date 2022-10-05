#ifndef EVO_TOOLS_BAR_H
#define EVO_TOOLS_BAR_H
#include <Bars/toolsBar.h>


class EvoToolsBar : public ToolsBar 
{
    private:

        static const int toolsBarChoiceCount = 4;
        std::string toolsBarChoices[toolsBarChoiceCount] = 
        {
            "Save current state",
            "Load state",
            "Pause",
            "Exit",
        };
        enum toolsBarChoicesConst {Save, Load, Pause, Exit};

        void menuControllSelect() override;
        void writeString(int count) override;

    public:
        EvoToolsBar(){
            this->barTitle = "~TOOLS~";

            this->choicesCount = toolsBarChoiceCount;
            this->rows = toolsBarChoiceCount / 2;
            this->columns = toolsBarChoiceCount / rows;

            this->firstToolsBarTitle = Save;
            this->lastToolsBarTitle = Exit;
        }

};

#endif