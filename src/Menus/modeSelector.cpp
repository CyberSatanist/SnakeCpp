#include "modeSelector.h"
#include <SnakeGame/snakeGame.h>
#include <Evolution/evolution.h>
#include <LifeGame/lifeGame.h>


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
