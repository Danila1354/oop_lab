#include "AbilityManager.h"

AbilityManager::AbilityManager() {
    initializeAbilityBuilders();
    shuffleAbilityBuilders();
}

void AbilityManager::initializeAbilityBuilders() {
    all_ability_builders.push_back(std::make_shared<DoubleDamageBuilder>());
    all_ability_builders.push_back(std::make_shared<ScannerBuilder>());
    all_ability_builders.push_back(std::make_shared<BombardmentBuilder>());
}

void AbilityManager::shuffleAbilityBuilders() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(all_ability_builders.begin(), all_ability_builders.end(), g);
    for (auto &ability : all_ability_builders) {
        ability_builders.push(ability);
    }
}

void AbilityManager::useAbility(InfoHolder &info_holder) {
    if (ability_builders.empty()) {
        throw NoAbilitiesException();
    } else {
        auto &ability_builder = ability_builders.front();
        logger.printAbilityInfo(ability_builder->getAbilityName());
        auto ability = ability_builder->build(info_holder);
        auto ability_result = ability->apply();
        logger.printAbilityResult(ability_result);
        ability_builders.pop();
        if (ability_result == AbilityResult::ShipDestroyed)
            addRandomAbility();
    }
}

void AbilityManager::addRandomAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, all_ability_builders.size() - 1);
    int randomAbility = dist(gen);
    ability_builders.push(all_ability_builders[randomAbility]);
}
