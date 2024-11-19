#ifndef OOP_LAB2_ABILITYMANAGER_H
#define OOP_LAB2_ABILITYMANAGER_H

#include "AbilityBuilder.h"
#include "NoAbilitiesException.h"
#include "DoubleDamageBuilder.h"
#include "ScannerBuilder.h"
#include "BombardmentBuilder.h"
#include <queue>
#include <random>

class AbilityManager {
private:
    std::queue<std::unique_ptr<AbilityBuilder>> ability_builders;
public:

    AbilityManager();

    void useAbility(GameField &field);

    void addRandomAbility();
};


#endif //OOP_LAB2_ABILITYMANAGER_H
