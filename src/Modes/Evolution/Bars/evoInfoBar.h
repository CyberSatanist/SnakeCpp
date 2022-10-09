#ifndef EVO_INFO_BAR_H
#define EVO_INFO_BAR_H
#include <Bars/infoBar.h>

class EvoInfoBar : public InfoBar
{
    private:

        static const int infoBarChoiceCount = 8;

        std::string infoBarChoices[infoBarChoiceCount] = 
        {
            "Gen.",
            "Best Id",
            "Alive",
            "Time",

            "Best Score",
            "Score",
            "Turns",
            "Speed"
        };
        
        enum infoBarChoicesConst {Generation, BestSnakeId, Alive, Time, BestScore, Score, Turn, Speed};

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