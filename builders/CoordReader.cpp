#include "CoordReader.h"

std::pair<int, int> CoordReader::read() {
    int x, y;
    std::cout << "Enter x and y: ";
    std::cin >> x >> y;
    return std::make_pair(x, y);
}