#ifndef SCREEN_H
#define SCREEN_H
#include <ncurses.h>

class Screen
{

    protected:
        int hight, width, key;
        enum { colors_count = 8 };

    public:
		static constexpr int all_colors[colors_count] = {
		    COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW,
			COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE
		};
	
		enum  controll_keys {
	    	UP, DOWN, LEFT, RIGHT, SELECT, ESCAPE, NOTHING
		};
        
		Screen();
		int getHight() { return hight ;}
		int getWidth() { return width ;}
		controll_keys controllHandler();
		void endFrame();
		void clearScreen();
		void writeText(const char* text);
		void setCursor(int x, int y);
		void setColor(int fg, int bg);
		void finishWindow();

};
#endif
