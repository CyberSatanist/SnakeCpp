#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Screen/screen.h>

extern Screen currentScreen;

class Parameters {

    public:
        //Main parameters
        bool gameOn = false;
        int whiteColor = COLOR_WHITE;

        //Field-ToolsMenu scale
        int fieldX = 3;
        int fieldMaxX = 4;
        int fieldY = 3;
        int fieldMaxY = 4;

        //Size of info bar
        int infoBarStartX = 0;
        int infoBarStartY = currentScreen.getWidth() / fieldMaxY * fieldY + 1;
        int infoBarEndX = currentScreen.getHight() / fieldMaxX * fieldX;
        int infoBarEndY = currentScreen.getWidth();

        //Size if tools bar
        int toolsBarStartX = currentScreen.getHight() / fieldMaxX * fieldX + 1;
        int toolsBarStartY = 0;
        int toolsBarEndX = currentScreen.getHight();
        int toolsBarEndY = currentScreen.getWidth() / fieldMaxY * fieldY;

        //Size of square bar
        int squareBarStartX = currentScreen.getHight() / fieldMaxX * fieldX + 1;
        int squareBarStartY = currentScreen.getWidth() / fieldMaxY * fieldY + 1;
        int squareBarEndX = currentScreen.getHight();
        int squareBarEndY = currentScreen.getWidth();

        //Viewed size of field
        int currentFieldSizeX = currentScreen.getHight() / fieldMaxX * fieldX;
        int currentFieldSizeY = currentScreen.getWidth() / fieldMaxY * fieldY;

        //Full size of field
        int fullFieldSizeX = currentFieldSizeX;
        int fullFieldSizeY = currentFieldSizeY;

};

#endif
