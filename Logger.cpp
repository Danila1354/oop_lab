#include "Logger.h"

void Logger::printAbilityInfo(std::string ability_name) {
    std::cout << "Ability " << ability_name << " activated" << '\n';
}

void Logger::printAbilityResult(AbilityResult result) {
    std::cout << "Ability result: ";
    switch (result) {
        case AbilityResult::Success:
            std::cout << "Ability successfully applied" << '\n';
            break;
        case AbilityResult::ShipDetected:
            std::cout << "In this area detected ship" << '\n';
            break;
        case AbilityResult::ShipNotDetected:
            std::cout << "In this area not detected ship" << '\n';
            break;
        default:
            break;
    }
}