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


std::vector<int> ShipManager::getShipsLengths() {
    std::vector<int> ship_lengths;
    for (auto &ship: ships) {
        ship_lengths.push_back(ship.getLength());
    }
    return ship_lengths;
}