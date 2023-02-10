#ifndef LIFE_GAME_H
#define LIFE_GAME_H

#include "Screen/screen.h"
#include "LifeGame/Field/lifeField.h"
#include "LifeGame/Bars/lifeInfoBar.h"
#include "LifeGame/Bars/lifeToolsBar.h"
#include "LifeGame/Bars/lifeSquareBar.h"
#include "LifeGame/Parameters/lifeGameParameters.h"

extern LifeGameParameters lifeGameParameters;

extern Screen currentScreen;


class LifeGame
{
    private:
        LifeField field;
        LifeInfoBar infoBar;
        LifeToolsBar toolsBar;
        LifeSquareBar squareBar;

        int key = 0;

        void turn();
        void drawScreen();

    public:
	    LifeGame()
            : field(
                lifeGameParameters.currentFieldSizeX,
                lifeGameParameters.currentFieldSizeY,
                lifeGameParameters.fullFieldSizeX * 2,
                lifeGameParameters.fullFieldSizeY * 2
            ), 
            infoBar(
                lifeGameParameters.infoBarStartX,
                lifeGameParameters.infoBarStartY,
                lifeGameParameters.infoBarEndX,
                lifeGameParameters.infoBarEndY
            ),
            toolsBar(
                lifeGameParameters.toolsBarStartX,
                lifeGameParameters.toolsBarStartY, 
                lifeGameParameters.toolsBarEndX, 
                lifeGameParameters.toolsBarEndY
            ),
            squareBar(
                lifeGameParameters.squareBarStartX,
                lifeGameParameters.squareBarStartY, 
                lifeGameParameters.squareBarEndX, 
                lifeGameParameters.squareBarEndY
            ) {};
        ~LifeGame() {};
	    void run();
};
#endif
