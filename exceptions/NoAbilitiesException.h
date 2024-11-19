#ifndef OOP_LAB2_NOABILITIESEXCEPTION_H
#define OOP_LAB2_NOABILITIESEXCEPTION_H
#include "BattleShipException.h"

class NoAbilitiesException : public BattleShipException {
public:
    NoAbilitiesException() : BattleShipException("No abilities available to use") {}
};

#endif
