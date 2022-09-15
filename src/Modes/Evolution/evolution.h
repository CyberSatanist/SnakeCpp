#ifndef EVOLUTION_H
#define EVOLUTION_H
#include "../../Screen/screen.h"
#include "Field/map.h"
#include <string>

class Evolution
{
    private:
        Screen currentScreen;
        int key;
        Map map;

        void turn();
        void drawScreen();
        void drawField();
        void drawToolsMenu();
       
    public:
	    Evolution(Screen screen);
	    void run();
};
#endif
