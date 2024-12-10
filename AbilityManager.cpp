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



void AbilityManager::to_json(json &j) {
    std::queue<std::shared_ptr<AbilityBuilder>> temp;
    while (!ability_builders.empty()) {
        temp.push(ability_builders.front());
        ability_builders.pop();
    }
    if (temp.empty()){
        j["abilities"] = "None";
    } else {
        j["abilities"] = json::array();
        while (!temp.empty()) {
            auto ability = temp.front();
            ability_builders.push(ability);
            temp.pop();
            j["abilities"].push_back(ability->getAbilityName());
        }
    }
}

void AbilityManager::from_json(const json &j) {
    if (j["abilities"] == "None") {
        ability_builders = std::queue<std::shared_ptr<AbilityBuilder>>();
        return;
    }
    for (auto &ability_name : j["abilities"]) {
        ability_builders.push(ability_builders_map[ability_name]);
    }
}