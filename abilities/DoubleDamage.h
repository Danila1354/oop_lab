#ifndef OOP_LAB2_DOUBLEDAMAGE_H
#define OOP_LAB2_DOUBLEDAMAGE_H
#include "Ability.h"

class DoubleDamage : public Ability {
private:
    int x, y;
public:
    DoubleDamage(int x, int y);
    bool apply(GameField &field) override;
};

#endif //OOP_LAB2_DOUBLEDAMAGE_H
