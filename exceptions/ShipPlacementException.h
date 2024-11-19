#ifndef OOP_LAB2_SHIPPLACEMENTEXCEPTION_H
#define OOP_LAB2_SHIPPLACEMENTEXCEPTION_H
#include "BattleShipException.h"

class ShipPlacementException : public BattleShipException {
public:
    ShipPlacementException()
            : BattleShipException("Cannot place ship at the given coordinates.") {}
};
#endif
