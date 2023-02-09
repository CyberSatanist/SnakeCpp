#ifndef STRAIGHT_NETWROK_H
#define STRAIGHT_NETWROK_H

#include "Evolution/Field/evoField.h"
#include "NeuralNetwork/network.h"


class StraightNetwork : public Network
{
    int *foodNeuronsUp;
    int *foodNeuronsDown;
    int *foodNeuronsLeft;
    int *foodNeuronsRight;
    int *wallNeuronsUp;
    int *wallNeuronsDown;
    int *wallNeuronsLeft;
    int *wallNeuronsRight;

    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    public:
        StraightNetwork();
        ~StraightNetwork();
        
        int useMind(EvoField &evoField, int headX, int headY);
        void mergeNetworks(StraightNetwork *parentOne, StraightNetwork *parentTwo);

        //Save-load
        void saveNetwork() {};
        void loadNetwork() {};
        

    private:
        int neuronActivity(int result);
        int validateResult(int result, int weight);

};

#endif