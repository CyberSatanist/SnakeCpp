#include "neuralNetworkSelector.h"
#include "Evolution/NeuralNetwork/standartNetwork/standartNetwork.h"
#include "Evolution/NeuralNetwork/straightNetwork/straightNetwork.h"
#include "Evolution/NeuralNetwork/simpleNetwork/simpleNetwork.h"
#include "Evolution/Parameters/evolutionParameters.h"

extern EvolutionParameters evolutionParameters;


NeuralNetworkSelector::NeuralNetworkSelector()
{
    menuTitle = "   ~N E U R A L  N E T W O R K  S E L E C T O R~   ";

    menuChoices = 
    {
        "Straight Netowrk",
        "Simple Network",
        "Standart Network",
    };
}


void NeuralNetworkSelector::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::StandartNetworkChoice){
        evolutionParameters.currentNetwork = EvolutionParameters::StandartNetworkType;
        menuOn = false;
    } else if (currentChoice == menuChoicesConst::StraightNetworkChoice){
        evolutionParameters.currentNetwork = EvolutionParameters::StraightNetworkType;
        menuOn = false;
    } else if (currentChoice == menuChoicesConst::SimpleNetworkChoice){
        evolutionParameters.currentNetwork = EvolutionParameters::SimpleNetworkType;
        menuOn = false;
    }
}
