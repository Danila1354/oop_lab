#include "AbilityManager.h"

AbilityManager::AbilityManager() {
    initializeAbilityBuilders();
    shuffleAbilityBuilders();
}

void AbilityManager::initializeAbilityBuilders() {
    ability_builders_map["DoubleDamage"] = std::make_shared<DoubleDamageBuilder>();
    ability_builders_map["Scanner"] = std::make_shared<ScannerBuilder>();
    ability_builders_map["Bombardment"] = std::make_shared<BombardmentBuilder>();
}

void AbilityManager::shuffleAbilityBuilders() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<std::shared_ptr<AbilityBuilder>> all_ability_builders;
    for (auto& pair : ability_builders_map) {
        all_ability_builders.push_back(pair.second);
    }
    std::shuffle(all_ability_builders.begin(), all_ability_builders.end(), g);

    for (auto& ability : all_ability_builders) {
        ability_builders.push(ability);
    }
}

AbilityResult AbilityManager::useAbility(InfoHolder &info_holder) {
    if (ability_builders.empty()) {
        throw NoAbilitiesException();
    } else {
        auto &ability_builder = ability_builders.front();
        logger.printAbilityInfo(ability_builder->getAbilityName());
        auto ability = ability_builder->build(info_holder);
        auto ability_result = ability->apply();
        logger.printAbilityResult(ability_result);
        ability_builders.pop();
        return ability_result;
    }
}

void AbilityManager::addRandomAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, ability_builders_map.size() - 1);
    auto it = ability_builders_map.begin();
    std::advance(it, dist(gen));
    ability_builders.push(it->second);
}

std::ostream &operator<<(std::ostream &out, AbilityManager &ability_manager) {
    for (auto& pair : ability_manager.ability_builders_map) {
        out << pair.first << std::endl;
    }
    return out;
}

std::istream &operator>>(std::istream &in, AbilityManager &ability_manager) {
    std::string ability_name;
    while (in >> ability_name) {
        auto it = ability_manager.ability_builders_map.find(ability_name);
        ability_manager.ability_builders.push(it->second);
    }
    return in;
}