#ifndef LIFE_GAME_H
#define LIFE_GAME_H
#include "../../Screen/screen.h"
#include "Field/lifeMap.h"
#include "Menus/SubMenus/lifeInfoSubMenu.h"
#include "Menus/SubMenus/lifeToolsSubMenu.h"

extern Screen currentScreen;

class LifeGame
{
    private:
        LifeMap map;
        LifeInfoSubMenu infoSubMenu;
        LifeToolsSubMenu toolsSubMenu;

        int key;

        void turn();
        void drawScreen();

    public:
	    LifeGame();
	    void run();
};
#endif
