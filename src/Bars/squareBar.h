#ifndef SQUARE_BAR_H
#define SQUARE_BAR_H
#include <Screen/screen.h>
#include <string>

extern Screen currentScreen;

class SquareBar
{
    protected:
        std::string barTitle;

        bool squareBarOn = false;

        int squareBarXStart;
        int squareBarYStart;
        int squareBarXEnd;
        int squareBarYEnd;


    public:
        void initSquareBar(int xStart, int yStart, int xEnd, int yEnd);
        virtual void drawInfoBar() {};

};

#endif