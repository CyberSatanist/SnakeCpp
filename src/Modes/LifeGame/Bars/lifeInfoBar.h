#ifndef LIFE_INFO_BAR_H
#define LIFE_INFO_BAR_H
#include <Bars/infoBar.h>

class LifeInfoBar : public InfoBar
{
    private:

        static const int infoBarChoiceCount = 1;
        std::string infoBarChoices[infoBarChoiceCount] = 
        {
            "Turn"
        };

        enum infoBarChoicesConst {Turn};

        int getParameter(int count) override;
        void writeString(int count) override;

    public:
        LifeInfoBar() {
            this->barTitle = "~INFORMATION~";

            this->rows = infoBarChoiceCount;
            this->columns = infoBarChoiceCount / rows;



            this->firstInfoBarTitle = Turn;
            this->lastInfoBarTitle = Turn;

        };
};

#endif