#include "CoordHolder.h"

void CoordHolder::readCoords() {
    CoordReader coord_reader;
    coords = coord_reader.read();
}

std::pair<int, int> CoordHolder::get_coords() {
    return coords;
}

