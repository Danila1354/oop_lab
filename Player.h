#ifndef OOP_LAB2_PLAYER_H
#define OOP_LAB2_PLAYER_H
#include "Character.h"
#include "AbilityManager.h"


class Player : public Character {
protected:
    AbilityManager &ability_manager;
    AbilityResult ability_result;
public:
    Player(GameField &field, ShipManager &ship_manager, AbilityManager &ability_manager);

    AbilityResult useAbility(Character &enemy);

    void attack(GameField &enemy_field, int x, int y) override;

    AbilityManager &getAbilityManager();


};


#endif //OOP_LAB2_PLAYER_H
