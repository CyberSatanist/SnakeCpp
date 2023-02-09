#include <Menus/mainmenu.h>
#include <Screen/screen.h>
#include <Database/database.h>
#include <SnakeGame/Parameters/snakeParameters.h>
#include <Evolution/Parameters/evolutionParameters.h>
#include <LifeGame/Parameters/lifeGameParameters.h>

Screen currentScreen;
SnakeParameters snakeParameters;
EvolutionParameters evolutionParameters;
LifeGameParameters lifeGameParameters;
Database database;


int main()
{
    MainMenu mainMenu;
    mainMenu.run();
 
    return 0;
}
