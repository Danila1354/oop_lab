#ifndef OOP_LAB2_INVALIDSHIPINDEXEXCEPTION_H
#define OOP_LAB2_INVALIDSHIPINDEXEXCEPTION_H
#include "BattleShipException.h"

class InvalidShipIndexException : public BattleShipException {
public:
    InvalidShipIndexException() : BattleShipException("Invalid ship index") {}
};


#endif //OOP_LAB2_INVALIDSHIPINDEXEXCEPTION_H
