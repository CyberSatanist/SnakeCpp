#include "screen.h"

#ifdef LINUX

Screen::Screen()
{
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    start_color();
    getmaxyx(stdscr, hight, width);
}

void Screen::endFrame() 
{
    refresh();
}

void Screen::clearScreen() 
{
    curs_set(0);
    refresh();
    erase();
}

void Screen::writeText(const char* text) 
{
    addstr(text);
}

void Screen::setCursor(int x, int y)
{
    move(x , y);
}

void Screen::finishWindow()
{
    endwin();
}

void Screen::setColor(int fg, int bg)
{
    int n  = bg*8 + fg + 1;
    init_pair(n, fg, bg);
    attrset(COLOR_PAIR(n));
}


Screen::controll_keys Screen::controllHandler()
{
    if (key = getch())
    {
        if (key == 259 | key == 119 | key == 87 | key == 134 | key == 166){
            return UP;
        } else if (key == 258 | key == 115 | key == 83 | key == 139 | key == 171){
            return DOWN;
        } else if (key == 260 | key == 97 | key == 65 | key == 132 | key == 164){
            return LEFT;
        } else if (key == 261 | key == 100 | key == 68 | key == 178 | key == 146){
            return RIGHT;
        } else if (key == 10){
            return SELECT;
        } else if (key == 27){
            return ESCAPE;
        }
    }
    return NOTHING;
}

#elif WINDOWS

#endif
