#ifndef STRAIGHT_NEURON_H
#define STRAIGHT_NEURON_H

class StraightNeuron
{
    public:
        StraightNeuron();

        int neuronId;
        int input;
        int direction;

        struct Connections {
            StraightNeuron *currentNeuron;
            struct Connections *nextConnection;
        };
        Connections* firstConnection;
        Connections* tmpConnection;
        Connections* tmpSecondConnection;

        struct Reactions {
            int up;
            int down;
            int left;
            int right;
        };
        Reactions* foodReaction;
        Reactions* wallReaction;
        Reactions* freeReaction;
        Reactions* snakeReaction;
        Reactions* resultReaction;

        void deleteNeuron();
};

#endif