#include "DoubleDamage.h"


DoubleDamage::DoubleDamage(int x, int y, GameField& field) : x(x), y(y), field(field) {}


AbilityResult DoubleDamage::apply() {
    field.attackCell(x, y);
    if (field.attackCell(x, y)) {
        return AbilityResult::ShipDestroyed;
    }
    return AbilityResult::Success;
}
