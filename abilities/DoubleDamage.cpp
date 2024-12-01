#include "DoubleDamage.h"


DoubleDamage::DoubleDamage(int x, int y, GameField& field) : x(x), y(y), field(field) {}


AbilityResult DoubleDamage::apply() {
    return AbilityResult::DoubleAttack;
}
