#ifndef MENU_H
#define MENU_H

#include "../Screen/screen.h"

class Menu
{

    protected:
	
	int currentChoice = 0;
	Screen currentScreen;

    public:
	void initScreen(Screen screen)
	{
	    currentScreen = screen;	
	};
	virtual void run(){};
        
	void setMenuChosenColor(){
	   currentScreen.setColor(COLOR_BLACK, COLOR_WHITE);
	};
        
	void setMenuLineColor(){
	   currentScreen.setColor(COLOR_WHITE, COLOR_BLACK);
	};

};
#endif
