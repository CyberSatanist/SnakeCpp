#ifndef STRAIGHT_NEURON_H
#define STRAIGHT_NEURON_H

class StraightNeuron
{
    public:
        StraightNeuron();

        int neuronId;
        int input = 0;
        int direction = 0;

        struct Connections {
            StraightNeuron *currentNeuron = nullptr;
            struct Connections *nextConnection = nullptr;
        };
        Connections *firstConnection = nullptr;
        Connections *tmpConnection = nullptr;
        Connections *tmpSecondConnection = nullptr;

        struct Reactions {
            int up = 0;
            int down = 0;
            int left = 0;
            int right = 0;
        };
        Reactions *foodReaction = nullptr;
        Reactions *wallReaction = nullptr;
        Reactions *freeReaction = nullptr;
        Reactions *snakeReaction = nullptr;
        Reactions *resultReaction = nullptr;

        void deleteNeuron();
};

#endif