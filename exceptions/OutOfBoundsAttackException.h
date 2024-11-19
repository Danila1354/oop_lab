#ifndef OOP_LAB2_OUTOFBOUNDSATTACKEXCEPTION_H
#define OOP_LAB2_OUTOFBOUNDSATTACKEXCEPTION_H
#include "BattleShipException.h"

class OutOfBoundsAttackException : public BattleShipException {
public:
    OutOfBoundsAttackException()
            : BattleShipException("Attack coordinates are out of bounds") {}
};

#endif
