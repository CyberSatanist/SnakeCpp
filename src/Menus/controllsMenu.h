#ifndef CONTROLLSMENU_H
#define CONTROLLSMENU_H

#include "menu.h"

class ControllsMenu : public Menu
{
    public:
        ControllsMenu();
        ~ControllsMenu() {};

    private:
        enum menuChoicesConst {Back};

        void menuControllSelect() override;
        
};
#endif
