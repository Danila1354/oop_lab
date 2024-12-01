#ifndef OOP_LAB2_CHARACTER_H
#define OOP_LAB2_CHARACTER_H
#include "GameField.h"
#include "ShipManager.h"
#include "AbilityManager.h"

class Character {
protected:
    GameField &field;
    ShipManager &ship_manager;
public:
    Character(GameField &field, ShipManager &ship_manager);

    virtual void attack(GameField &enemy_field, int x, int y);
    void PlaceShips();
    GameField &getField();
    ShipManager &getShipManager();
};

#endif //OOP_LAB2_CHARACTER_H
