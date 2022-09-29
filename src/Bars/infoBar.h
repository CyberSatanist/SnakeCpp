#ifndef INFO_BAR_H
#define INFO_BAR_H
#include <Screen/screen.h>
#include <string>

extern Screen currentScreen;

class InfoBar
{
    protected:
        std::string barTitle;
        enum infoBarChoicesConst {}; 

        int count;
        int rows;
        int columns;
        bool infoBarOn = false;

        int infoBarXStart;
        int infoBarYStart;
        int infoBarXEnd;
        int infoBarYEnd;

        int firstInfoBarTitle;
        int currentInfoBarTitle;
        int lastInfoBarTitle;
        int currentInfoParameter;

        virtual int getParameter(int count) { return 0; };
        virtual void writeString(int count) {};
        void printParameter(int parameter);

    public:
        void initInfoBar(int xStart, int yStart, int xEnd, int yEnd);
        void drawInfoBar();

};

#endif