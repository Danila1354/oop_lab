#ifndef OOP_LAB2_DOUBLEDAMAGE_H
#define OOP_LAB2_DOUBLEDAMAGE_H
#include "Ability.h"

class DoubleDamage : public Ability {
private:
    int x, y;
    GameField &field;
public:
    DoubleDamage(int x, int y, GameField &field);
    AbilityResult apply() override;
};

#endif //OOP_LAB2_DOUBLEDAMAGE_H
