#ifndef OOP_LAB1_SHIPMANAGER_H
#define OOP_LAB1_SHIPMANAGER_H

#include <iostream>
#include "Ship.h"
#include "InvalidShipIndexException.h"

class ShipManager {
private:
    std::vector<Ship> ships;
public:
    ShipManager(int number_of_ships, const std::vector<int> &ship_sizes);

    std::vector<Ship> &getShips();
    Ship& getShipByIndex(int index);
    bool isAllShipsDestroyed();
    std::vector<int> getShipsLengths();
};


#endif //OOP_LAB1_SHIPMANAGER_H
