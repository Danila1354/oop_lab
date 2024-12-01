#include "Character.h"

Character::Character(GameField &field, ShipManager &ship_manager) : field(field), ship_manager(ship_manager) {};

GameField &Character::getField() {
    return field;
}

ShipManager &Character::getShipManager() {
    return ship_manager;
}

void Character::attack(GameField &enemy_field, int x, int y) {
    enemy_field.attackCell(x, y);
}

void Character::PlaceShips() {
    int ships_coords[3][2] = {{5, 4},
                              {1, 4},
                              {9, 1}};
    auto &ships = ship_manager.getShips();
    bool positions[] = {false, false, true};
    for (int i = 0; i < ships.size(); i++) {
        try {
            field.placeShip(ships[i], ships_coords[i][0], ships_coords[i][1], positions[i]);
        }
        catch (ShipPlacementException &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}