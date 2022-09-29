#ifndef LIFE_FIELD_H
#define LIFE_FIELD_H
#include <Field/field.h>

class LifeField : public Field {

    public:
        virtual void drawCell(int cellX, int cellY) override;

};
#endif
