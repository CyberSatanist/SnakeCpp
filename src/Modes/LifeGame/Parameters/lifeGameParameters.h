#ifndef LIFE_GAME_PARAMETERS_H
#define LIFE_GAME_PARAMETERS_H

#include <Parameters/parameters.h>

class LifeGameParameters : public Parameters
{
    public:
        int delayDuration = 80;
        bool pauseOn = false;
        bool reset = false;
        bool clean = false;
        bool moveField = false;
        bool drawCells = false;

        //Statistic info
        int turn = 0;
        int currentStartX = 0;
        int currentStartY = 0;
        int currentEndX = 0;
        int currentEndY = 0;

        //CellModel
        int cellsToLive;
        int cellStartBornChance = 2;
        int cellsCount = 0;
        
        int cellColor = COLOR_BLUE;
        int freeCellColor = COLOR_WHITE;
        int frameColor = COLOR_BLACK;

        //Full size of field
};

#endif
