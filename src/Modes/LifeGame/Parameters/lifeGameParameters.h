#ifndef LIFE_GAME_PARAMETERS_H
#define LIFE_GAME_PARAMETERS_H

#include <Parameters/parameters.h>

class LifeGameParameters : public Parameters
{
    public:
        int delayDuration = 5;

        //Statistic info
        int turn = 0;
        int currentStartX = 0;
        int currentStartY = 0;
        int currentEndX = 0;
        int currentEndY = 0;

        //CellModel
        int countOfCells = 10;
        int cellsToLive;
        
        int cellColor = COLOR_RED;
        int BackGroundColor = COLOR_RED;

        //Full size of field
};

#endif
