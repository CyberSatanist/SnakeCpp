#ifndef LIFE_GAME_PARAMETERS_H
#define LIFE_GAME_PARAMETERS_H

class LifeGameParameters 
{
    public:
        bool lifeGameOn = false;
        int delayDuration = 5;
        int whiteColor = COLOR_WHITE;

//Field-ToolsMenu
        int fieldX = 3;
        int fieldMaxX = 4;
        int fieldY = 3;
        int fieldMaxY = 4;

//Statistic info
        int turn = 0;
        int currentStartX = 0;
        int currentStartY = 0;
        int currentEndX = 0;
        int currentEndY = 0;

//MapSize
        int MapSizeX;
        int MapSizeY;

//CellModel
        int countOfCells = 10;
        int cellsToLive;
        
        int cellColor = COLOR_RED;
        int BackGroundColor = COLOR_RED;

};

#endif
