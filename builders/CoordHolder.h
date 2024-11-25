#ifndef OOP_LAB2_COORDHOLDER_H
#define OOP_LAB2_COORDHOLDER_H
#include "CoordReader.h"
class CoordHolder{
private:
    std::pair<int, int> coords;
public:
    void readCoords();
    std::pair<int, int> get_coords();

};


#endif //OOP_LAB2_COORDHOLDER_H
