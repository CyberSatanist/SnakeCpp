#ifndef NEURAL_NETWORK_SELECTOR_H
#define NEURAL_NETWORK_SELECTOR_H

#include "menu.h"


class NeuralNetworkSelector : public Menu
{
    public:
        NeuralNetworkSelector();
        ~NeuralNetworkSelector() {};


    private:

        enum menuChoicesConst 
	    {
            StraightNetworkChoice,
            SimpleNetworkChoice,
            StandartNetworkChoice, 
	    };

        void menuControllSelect() override;
        
};
#endif
