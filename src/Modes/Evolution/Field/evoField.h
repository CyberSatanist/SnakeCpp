#ifndef EVO_FIELD_H
#define EVO_FIELD_H

#include "Field/field.h"
#include "Evolution/Parameters/evolutionParameters.h"

extern EvolutionParameters evolutionParameters;


class EvoField : public Field
{
    public:
        EvoField(int currentX, int currentY, int fullX, int fullY);
        ~EvoField() {};

        void drawCell(int cellX, int cellY) override;

        void drawSnakeAndFood();

};
#endif
