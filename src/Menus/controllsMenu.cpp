#include "controllsMenu.h"


ControllsMenu::ControllsMenu()
{
    menuTitle = "   ~C O N T R O L L S   M E N U~   ";

    menuChoices = 
    {
        "Up  =>  [W, w, (Upper arrow)]",
        "Down  =>  [S, s, (Bottom arrow)]",
        "Left  => [A, a, (Left arrow)]",
        "Right  =>  [D, d, (Right arrow)]",
        "Menu  =>  [Esc]",
        "Select  =>  [Enter]",
        "Back"
    };
}


void ControllsMenu::menuControllSelect()
{
    menuOn = false;
}