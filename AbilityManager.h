#ifndef OOP_LAB2_ABILITYMANAGER_H
#define OOP_LAB2_ABILITYMANAGER_H

#include "AbilityBuilder.h"
#include "NoAbilitiesException.h"
#include "DoubleDamageBuilder.h"
#include "ScannerBuilder.h"
#include "BombardmentBuilder.h"
#include <queue>
#include <random>
#include <Logger.h>

class AbilityManager {
private:
    std::queue<std::shared_ptr<AbilityBuilder>> ability_builders;
    std::vector<std::shared_ptr<AbilityBuilder>> all_ability_builders;
    Logger logger;
public:

    AbilityManager();

    void useAbility(InfoHolder& info_holder);

    void initializeAbilityBuilders();

    void shuffleAbilityBuilders();

    void addRandomAbility();
};


#endif //OOP_LAB2_ABILITYMANAGER_H
