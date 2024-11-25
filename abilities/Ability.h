#ifndef OOP_LAB2_ABILITY_H
#define OOP_LAB2_ABILITY_H
#include "GameField.h"

enum class AbilityResult{
    Success,
    ShipDestroyed,
    ShipDetected,
    AllShipsDestroyed,
    ShipNotDetected
};
class Ability {
public:
    virtual AbilityResult apply() = 0;
    virtual ~Ability() = default;
};

#endif //OOP_LAB2_ABILITY_H
