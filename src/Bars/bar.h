#ifndef BAR_H
#define BAR_H

#include <string>
#include <vector>
#include "Screen/screen.h"

extern Screen currentScreen;


class Bar
{
  public:
        Bar(int xStart, int yStart, int xEnd, int yEnd) : startX(xStart), startY(yStart), endX(xEnd), endY(yEnd) {};
        ~Bar() {};

        virtual void drawBar() {};


    protected:
        std::string barTitle;
        std::vector<std::string> barChoices;

        int startX;
        int startY;
        int endX;
        int endY;

        bool barOn = false;

        int rows = 0;
        int columns = 0;
        int currentColumn = 0;
        int currentRow = 0;
        int currentChoice = 0;

        enum barChoicesConst {};

        int firstBarTitle = 0;
        int lastBarTitle = 0;

        void drawBorders();
        void printParameter(int parameter);
        void writeString(int count);

};

#endif