#include "ShipManager.h"

ShipManager::ShipManager(int number_of_ships, const std::vector<int> &ship_sizes) {
    for (int i = 0; i < number_of_ships; i++) {
        ships.emplace_back(Ship(ship_sizes[i]));
    }
}

std::vector<Ship> &ShipManager::getShips() {
    return ships;
}

Ship& ShipManager::getShipByIndex(int index){
    if (0<=index<ships.size()){
        return ships[index];
    }
    throw InvalidShipIndexException();

}

bool ShipManager::isAllShipsDestroyed() {
    for (auto &ship: ships) {
        if (!ship.isShipDestroyed()) {
            return false;
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &out, ShipManager &ship_manager) {
    for (auto &ship : ship_manager.ships) {
        out << ship.getLength() << std::endl;
    }
    return out;
}

std::istream &operator>>(std::istream &in, ShipManager &ship_manager) {
    int ship_size;
//    ship_manager.ships.clear();
    while (in >> ship_size) {
        ship_manager.ships.emplace_back(Ship(ship_size));
    }
    return in;
}