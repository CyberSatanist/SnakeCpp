#ifndef EVOLUTION_H
#define EVOLUTION_H
#include "../../Screen/screen.h"
#include "Menus/SubMenus/infoSubMenu.h"
#include "Menus/SubMenus/toolsSubMenu.h"
#include "Field/map.h"
#include <string>

class Evolution
{
    private:
        Map map;
        Screen currentScreen;
        InfoSubMenu infoSubMenu;
        ToolsSubMenu toolsSubMenu;

        int key;

        void turn();
        void drawScreen();
       
    public:
	    Evolution(Screen screen);
	    void run();
};
#endif
