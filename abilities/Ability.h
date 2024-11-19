#ifndef OOP_LAB2_ABILITY_H
#define OOP_LAB2_ABILITY_H
#include "GameField.h"

class Ability {
public:
    virtual bool apply(GameField &field) = 0;
    virtual ~Ability() = default;
};

#endif //OOP_LAB2_ABILITY_H
