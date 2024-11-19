#ifndef OOP_LAB2_BOMBARDMENT_H
#define OOP_LAB2_BOMBARDMENT_H


#include "Ability.h"
#include <vector>
#include <random>

class Bombardment : public Ability {
public:
    bool apply(GameField &field) override;
};


#endif //OOP_LAB2_BOMBARDMENT_H
