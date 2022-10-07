#ifndef EVO_FIELD_H
#define EVO_FIELD_H
#include <Field/field.h>
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;


class EvoField : public Field {

    public:
        void drawCell(int cellX, int cellY) override;

        void initEvoField();
        void drawSnakeAndFood();

};
#endif
