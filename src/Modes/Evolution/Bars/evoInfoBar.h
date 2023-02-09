#ifndef EVO_INFO_BAR_H
#define EVO_INFO_BAR_H
#include "Bars/infoBar.h"

class EvoInfoBar : public InfoBar
{
    public:
        EvoInfoBar(int xStart, int yStart, int xEnd, int yEnd);
        ~EvoInfoBar() {};


    private:
        enum barChoicesConst {
            Generation, BestSnakeId, MaxFood, Alive, MutChance, TurnsToDeath, Time,
            BestScore,  Score,       Food,    Turn,  TurnsLeft, Borders,      Speed
        };

        int getParameter(int count) override;

};

#endif