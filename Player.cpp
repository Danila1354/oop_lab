#include "Player.h"

Player::Player(GameField &field, ShipManager &ship_manager, AbilityManager &ability_manager) :
        Character(field, ship_manager), ability_manager(ability_manager), ability_result(AbilityResult::None) {};

AbilityResult Player::useAbility(Character &enemy) {
    try {
        InfoHolder info_holder = InfoHolder(enemy.getField(), enemy.getShipManager());
        ability_result = ability_manager.useAbility(info_holder);
    }
    catch (NoAbilitiesException &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Player::attack(GameField &enemy_field, int x, int y) {
    if (enemy_field.attackCell(x, y, ability_result == AbilityResult::DoubleAttack)) {
        ability_manager.addRandomAbility();
    }
}

AbilityManager &Player::getAbilityManager() {
    return ability_manager;
}