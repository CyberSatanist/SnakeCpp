#include "standartNeuron.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;

StandartNeuron::StandartNeuron()
{
    neuronId = evolutionParameters.neuronIdCounter;
    evolutionParameters.neuronIdCounter++;
}