#include "Cell.h"

Cell::Cell(bool is_open) : is_open(is_open), status(Status::Empty), pointer_to_ship(nullptr),
index_of_segment(-1) {}


void Cell::open() {
    is_open = true;
}
bool Cell::isOpen(){
    return is_open;
}
void Cell::setStatus(Status status) {
    this->status = status;
}

Status Cell::getStatus() {
    return status;
}

Ship *Cell::getPointerToShip() {
    return pointer_to_ship;
}

void Cell::setPointerToShip(Ship *pointer_to_ship) {
    this->pointer_to_ship = pointer_to_ship;
}


void Cell::setIndexOfSegment(int index) {
    index_of_segment = index;
}

int Cell::getIndexOfSegment() {
    return index_of_segment;
}


