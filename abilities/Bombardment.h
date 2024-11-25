#ifndef OOP_LAB2_BOMBARDMENT_H
#define OOP_LAB2_BOMBARDMENT_H


#include "Ability.h"
#include <vector>
#include <random>

class Bombardment : public Ability {
private:
    ShipManager &ship_manager;
public:
    Bombardment(ShipManager &ship_manager);
    AbilityResult apply() override;
};


#endif //OOP_LAB2_BOMBARDMENT_H
