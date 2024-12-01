#ifndef OOP_LAB2_INFOHOLDER_H
#define OOP_LAB2_INFOHOLDER_H
#include <iostream>
#include "GameField.h"
#include "ShipManager.h"
#include "CoordHolder.h"
class InfoHolder {

public:
    GameField &field;
    ShipManager &ship_manager;
    CoordHolder coord_holder;
    InfoHolder(GameField &field, ShipManager &ship_manager) : field(field), ship_manager
    (ship_manager), coord_holder(CoordHolder()) {}
};


#endif //OOP_LAB2_INFOHOLDER_H
