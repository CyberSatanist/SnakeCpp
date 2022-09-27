#include "../Menus/mainmenu.h"

#include "../Screen/screen.h"
#include "../Modes/SnakeGame/Parameters/snakeParameters.h"
#include "../Modes/Evolution/Parameters/evolutionParameters.h"
#include "../Modes/LifeGame/Parameters/lifeGameParameters.h"

Screen currentScreen;
SnakeParameters snakeParameters;
EvolutionParameters evolutionParameters;
LifeGameParameters lifeGameParameters;


int main()
{
    MainMenu mainMenu;
    
    mainMenu.run();

    currentScreen.finishWindow();
 
    return 0;
}
