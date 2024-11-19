#ifndef OOP_LAB1_SHIP_H
#define OOP_LAB1_SHIP_H

#include <iostream>

enum class SegmentState{
    FULL, Damaged, Destroyed
};

class Ship {
private:
    unsigned short length;
    std::vector<SegmentState> segments;
    bool is_vertical;

    bool checkLength(int length);

public:
    Ship(unsigned short length);

    void takeDamage(int index);

    bool isShipDestroyed();

    unsigned short getLength();

    void setIsVertical(bool value);

    bool isVertical();

    SegmentState getSegmentState(int index);
};


#endif //OOP_LAB1_SHIP_H
