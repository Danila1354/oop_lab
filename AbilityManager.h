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
#include <unordered_map>
#include <functional>

class AbilityManager {
private:
    std::queue<std::shared_ptr<AbilityBuilder>> ability_builders;
    std::unordered_map<std::string, std::shared_ptr<AbilityBuilder>> ability_builders_map;
    Logger logger;
    void initializeAbilityBuilders();

    void shuffleAbilityBuilders();
public:

    AbilityManager();

    AbilityResult useAbility(InfoHolder& info_holder);

    void addRandomAbility();

    friend std::istream &operator>>(std::istream &in, AbilityManager &ability_manager);

    friend std::ostream &operator<<(std::ostream &out, AbilityManager &ability_manager);
};


#endif //OOP_LAB2_ABILITYMANAGER_H
