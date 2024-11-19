#include "AbilityManager.h"

AbilityManager::AbilityManager() {
    std::vector<std::unique_ptr<AbilityBuilder>> temp_ability_builders;
    temp_ability_builders.push_back(std::make_unique<DoubleDamageBuilder>());
    temp_ability_builders.push_back(std::make_unique<ScannerBuilder>());
    temp_ability_builders.push_back(std::make_unique<BombardmentBuilder>());
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(temp_ability_builders.begin(), temp_ability_builders.end(), g);
    for (auto &ability: temp_ability_builders) {
        ability_builders.push(std::move(ability));
    }
}

void AbilityManager::useAbility(GameField &field) {
    if (ability_builders.empty()) {
        throw NoAbilitiesException();
    } else {
        auto &ability_builder = ability_builders.front();
        if (ability_builder->getType() == AbilityType::DoubleDamage) {
            ability_builder->setCoords(5, 4);
        } else if (ability_builder->getType() == AbilityType::Scanner) {
            ability_builder->setCoords(0, 3);
        }
        auto ability = ability_builder->build();
        ability_builder->printInfo();
        if (ability->apply(field) && ability_builder->getType() != AbilityType::Scanner){
            ability_builders.pop();
            this->addRandomAbility();
        }
        else
            ability_builders.pop();
    }
}

void AbilityManager::addRandomAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);
    int randomAbility = dist(gen);
    switch (randomAbility) {
        case 0:
            ability_builders.push(std::make_unique<DoubleDamageBuilder>());
            break;
        case 1:
            ability_builders.push(std::make_unique<ScannerBuilder>());
            break;
        case 2:
            ability_builders.push(std::make_unique<BombardmentBuilder>());
            break;
    }
}