#ifndef CONTROLLSMENU_H
#define CONTROLLSMENU_H

#include <string>
#include "menu.h"

class ControllsMenu : public Menu {
    
    private:
        static const int controllsMenuChoiceCount = 7;
        bool controllsMenuOn = false;
        std::string controllsMenuChoices[controllsMenuChoiceCount] = {
            "Up  =>  [W, w, (Upper arrow)]",
            "Down  =>  [S, s, (Bottom arrow)]",
            "Left  => [A, a, (Left arrow)]",
            "Right  =>  [D, d, (Right arrow)]",
            "Menu  =>  [Esc]",
            "Select  =>  [Enter]",
            "Back"
        };
    
    public:
        void run() override;
        void menuFrame();
        void menuControllHandler();
};
#endif
