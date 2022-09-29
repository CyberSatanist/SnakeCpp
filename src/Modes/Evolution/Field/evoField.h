#ifndef EVO_FIELD_H
#define EVO_FIELD_H
#include <Field/field.h>

class EvoField : public Field {

    public:
        virtual void drawCell(int cellX, int cellY) override;

        void initEvoField();

};
#endif
