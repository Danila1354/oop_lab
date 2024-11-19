#ifndef OOP_LAB1_CELL_H
#define OOP_LAB1_CELL_H

#include "Ship.h"

enum class Status {
    Empty, Occupied
};

class Cell {
private:
    bool is_open;
    Status status;
    int index_of_segment;
    Ship *pointer_to_ship;


public:
    Cell();

    void display();

    void open();

    void setStatus(Status status);

    Status getStatus();

    Ship *getPointerToShip();

    void setPointerToShip(Ship *pointer_to_ship);

    void setIndexOfSegment(int index);

    int getIndexOfSegment();
    bool isOpen();

};


#endif //OOP_LAB1_CELL_H
