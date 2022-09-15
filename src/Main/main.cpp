#include <chrono>
#include <thread>
#include <unistd.h>

#include "../Screen/screen.h"
#include "../Menus/mainmenu.h"

int main()
{
    Screen screen;
    MainMenu mainMenu;
    
    mainMenu.initScreen(screen);
    mainMenu.run();

    screen.finishWindow();
 
    return 0;
}
