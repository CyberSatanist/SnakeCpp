#ifndef LIFE_FIELD_H
#define LIFE_FIELD_H

#include "Field/field.h"

class LifeField : public Field {

    int cursorX = 0;
    int cursorY = 0;
    bool isCursorSet = false;
    
    public:
        LifeField(int currentX, int currentY, int fullX, int fullY);
        ~LifeField() {};

        void drawCell(int cellX, int cellY) override;
        void makeTurn();
        void reset();
        void clean();
        bool onFrame(int x, int y) const;
        void moveHandler(int key);
        void drawCellsHandler(int key);

};
#endif
