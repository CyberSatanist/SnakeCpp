#ifndef LIFE_GAME_H
#define LIFE_GAME_H
#include <Screen/screen.h>
#include <LifeGame/Field/lifeField.h>
#include <LifeGame/Bars/lifeInfoBar.h>
#include <LifeGame/Bars/lifeToolsBar.h>
extern Screen currentScreen;

class LifeGame
{
    private:
        LifeField field;
        LifeInfoBar infoBar;
        LifeToolsBar toolsBar;

        int key = 0;

        void turn();
        void drawScreen();

    public:
	    LifeGame();
        ~LifeGame();
	    void run();
};
#endif
