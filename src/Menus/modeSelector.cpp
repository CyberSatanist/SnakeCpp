#include "modeSelector.h"
#include "../Modes/SnakeGame/snakeGame.h"
#include "../Modes/Evolution/evolution.h"
#include "../Modes/LifeGame/lifeGame.h"


void ModeSelector::menuControllSelect()
{
    SnakeGame snakeGame;
    Evolution evolution;
    LifeGame lifeGame;
    
    if (currentChoice == menuChoicesConst::SnakeGameChoice){
	    snakeGame.run();
    } else if (currentChoice == menuChoicesConst::EvolutionChoice){
	    evolution.run();
    } else if (currentChoice == menuChoicesConst::LifeGameChoice){
	    lifeGame.run();
    } else if (currentChoice == menuChoicesConst::Back){
        menuOn = false;
    }
}
