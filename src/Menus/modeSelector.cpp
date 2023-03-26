#include "modeSelector.h"
#include "neuralNetworkSelector.h"
#include "SnakeGame/snakeGame.h"
#include "Evolution/evolution.h"
#include "LifeGame/lifeGame.h"
#include "Evolution/NeuralNetwork/standartNetwork/standartNetwork.h"
#include "Evolution/NeuralNetwork/straightNetwork/straightNetwork.h"
#include "Evolution/NeuralNetwork/simpleNetwork/simpleNetwork.h"


ModeSelector::ModeSelector()
{
    menuTitle = "   ~M O D E  S E L E C T O R~   ";

    menuChoices = 
    {
        "Snake Game",
        "Evolution",
        "Life Game",
        "Back"
    };
}


void ModeSelector::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::SnakeGameChoice){
        SnakeGame *snakeGame = new SnakeGame;
	    snakeGame->run();
        delete snakeGame;
    } else if (currentChoice == menuChoicesConst::EvolutionChoice){
        NeuralNetworkSelector networkSelector;
        networkSelector.run();

        if (evolutionParameters.currentNetwork == EvolutionParameters::StandartNetworkType) {
            Evolution<StandartNetwork> *evolution = new Evolution<StandartNetwork>();
            evolution->run();
            delete evolution;
        } else if (evolutionParameters.currentNetwork == EvolutionParameters::SimpleNetworkType) {
            Evolution<SimpleNetwork> *evolution = new Evolution<SimpleNetwork>();
            evolution->run();
            delete evolution;
        } else if (evolutionParameters.currentNetwork == EvolutionParameters::StraightNetworkType) {
            Evolution<StraightNetwork> *evolution = new Evolution<StraightNetwork>();
            evolution->run();
            delete evolution;
        } else {
            Evolution<StandartNetwork> *evolution = new Evolution<StandartNetwork>();
            evolution->run();
            delete evolution;
        }
    } else if (currentChoice == menuChoicesConst::LifeGameChoice){
        LifeGame *lifeGame = new LifeGame;
	    lifeGame->run();
        delete lifeGame;
    } else if (currentChoice == menuChoicesConst::Back){
        menuOn = false;
    }
}
