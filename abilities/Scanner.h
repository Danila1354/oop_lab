#ifndef OOP_LAB2_SCANNER_H
#define OOP_LAB2_SCANNER_H

#include "Ability.h"
#include <iostream>

class Scanner : public Ability {
private:
    int x, y;
    GameField &field;
public:
    Scanner(int x, int y, GameField &field);
    AbilityResult apply() override;
};

#endif //OOP_LAB2_SCANNER_H
