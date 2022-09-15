#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include "menu.h"

class Settings : public Menu
{
    protected:
        std::string leftArrowString = " < ";
        std::string rightArrowString = " > ";
        std::string spaceString = "   ";
        const char *space = spaceString.c_str();
        const char *leftArrow = leftArrowString.c_str();
        const char *rightArrow = rightArrowString.c_str();
};
#endif
