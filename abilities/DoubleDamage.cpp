#include "DoubleDamage.h"


DoubleDamage::DoubleDamage(int x, int y) : x(x), y(y) {}

bool DoubleDamage::apply(GameField &field) {
    field.attackCell(x, y);
    return field.attackCell(x, y);
}
