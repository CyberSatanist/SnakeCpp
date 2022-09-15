#ifndef CONTROLLSMENU_H
#define CONTROLLSMENU_H

#include <string>
#include "menu.h"

class ControllsMenu : public Menu {
    
    private:
        static const int menuChoiceCount = 7;

        std::string menuChoices[menuChoiceCount] = {
            "Up  =>  [W, w, (Upper arrow)]",
            "Down  =>  [S, s, (Bottom arrow)]",
            "Left  => [A, a, (Left arrow)]",
            "Right  =>  [D, d, (Right arrow)]",
            "Menu  =>  [Esc]",
            "Select  =>  [Enter]",
            "Back"
        };

        enum menuChoicesConst {Back};

        //void menuFrame();
        void menuControllSelect() override;
    
    public:
        ControllsMenu() {
            this->menuConst = menuChoiceCount;
            this->menuTitle = "   ~C O N T R O L L S   M E N U~   ";
        };
};
#endif
