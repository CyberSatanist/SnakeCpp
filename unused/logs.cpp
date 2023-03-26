#include <fstream>
#include <cstring>
#include <iostream>


    std::ofstream neuronActivity;
    neuronActivity.open("logs/rating.txt");
    int count = 1;
    while(parentsList) {
        neuronActivity << "=== === Count === " <<  count++ << std::endl;
        neuronActivity << "=== === Score === " <<  parentsList->snakeScore << std::endl;
        neuronActivity << "=== === number === " <<  parentsList->snakeNumber << std::endl;
        neuronActivity << "\n" << std::endl;
        tempRating = parentsList;
        parentsList = parentsList->nextPlace;
        delete tempRating;
    }
    neuronActivity.close();
