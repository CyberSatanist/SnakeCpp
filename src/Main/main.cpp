#include <Menus/mainmenu.h>

#include <Screen/screen.h>
#include <SnakeGame/Parameters/snakeParameters.h>
#include <Evolution/Parameters/evolutionParameters.h>
#include <LifeGame/Parameters/lifeGameParameters.h>

#ifdef LOGS
    #include <Evolution/NeuralNetwork/standartNetwork.h>
#endif

Screen currentScreen;
SnakeParameters snakeParameters;
EvolutionParameters evolutionParameters;
LifeGameParameters lifeGameParameters;


int main()
{
    #ifdef LOGS
        StandartNetwork network;
        network.tests();
    #endif
    MainMenu mainMenu;
    
    mainMenu.run();

    currentScreen.finishWindow();
 
    return 0;
}
