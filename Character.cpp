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

void Character::randomPlaceShips() {
    auto& ships = ship_manager.getShips();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> width_dist(0, field.getWidth() - 1);
    std::uniform_int_distribution<> height_dist(0, field.getHeight() - 1);
    std::uniform_int_distribution<> orientation_dist(0, 1);

    for (auto &ship : ships) {
        while (true) {
            int x = width_dist(gen);
            int y = height_dist(gen);
            bool is_vertical = orientation_dist(gen);
            try {
                field.placeShip(ship, x, y, is_vertical);
                break;
            } catch (ShipPlacementException &e) {
                continue;
            }
        }
    }
}

