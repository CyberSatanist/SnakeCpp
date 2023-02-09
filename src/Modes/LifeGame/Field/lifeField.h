#ifndef LIFE_FIELD_H
#define LIFE_FIELD_H
#include "Field/field.h"

class LifeField : public Field {

    public:
        LifeField(int currentX, int currentY, int fullX, int fullY) : Field(currentX, currentY, fullX, fullY) {};
        ~LifeField() {};

        void drawCell(int cellX, int cellY) override;

};
#endif
