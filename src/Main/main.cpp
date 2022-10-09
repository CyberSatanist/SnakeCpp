#include <Menus/mainmenu.h>

#include <Screen/screen.h>
#include <SnakeGame/Parameters/snakeParameters.h>
#include <Evolution/Parameters/evolutionParameters.h>
#include <LifeGame/Parameters/lifeGameParameters.h>


//#include <Evolution/NeuralNetwork/standartNetwork.h>

Screen currentScreen;
SnakeParameters snakeParameters;
EvolutionParameters evolutionParameters;
LifeGameParameters lifeGameParameters;


int main()
{
    //StandartNetwork network;
    MainMenu mainMenu;
    
    mainMenu.run();

    currentScreen.finishWindow();
 
    return 0;
}
