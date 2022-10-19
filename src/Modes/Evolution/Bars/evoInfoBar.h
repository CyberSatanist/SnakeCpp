#ifndef EVO_INFO_BAR_H
#define EVO_INFO_BAR_H
#include <Bars/infoBar.h>

class EvoInfoBar : public InfoBar
{
    private:

        static const int infoBarChoiceCount = 12;

        std::string infoBarChoices[infoBarChoiceCount] = 
        {
            "Gen.",
            "Best Id",
            "Max Food",
            "Alive",
            "Mutations",
            "Time",

            "Best Score",
            "Score",
            "Placeholder",
            "Turns",
            "TurnsLeft",
            "Speed"
        };
        
        enum infoBarChoicesConst {Generation, BestSnakeId, MaxFood, Alive, MutChance, Time, BestScore, Score, Placeholder, Turn, TurnsLeft, Speed};

        int getParameter(int count) override;
        void writeString(int count) override;

    public:
        EvoInfoBar() {
            this->barTitle = "~INFORMATION~";

            this->rows = infoBarChoiceCount / 2;
            this->columns = infoBarChoiceCount / rows;

            this->firstInfoBarTitle = Generation;
            this->lastInfoBarTitle = Speed;

        };
};

#endif