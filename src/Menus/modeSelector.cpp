#include "modeSelector.h"
#include <array>
#include <charconv>
#include <iostream>
#include <sstream>
#include "../Modes/SnakeGame/snakeGame.h"
#include "../Modes/Evolution/evolution.h"


void ModeSelector::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::SnakeGameChoice){
        SnakeGame snakeGame(currentScreen);
	    snakeGame.run();
    } else if (currentChoice == menuChoicesConst::EvolutionChoice){
        Evolution evolution(currentScreen);
	    evolution.run();
    } else if (currentChoice == menuChoicesConst::Back){
        menuOn = false;
    }
}
