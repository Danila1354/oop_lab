#include "Scanner.h"


Scanner::Scanner(int x, int y, GameField& field) : x(x), y(y), field(field) {}



AbilityResult Scanner::apply() {
    int width = field.getWidth();
    int height = field.getHeight();
    bool flag = false;
    if (x == width - 2) x -= 1;
    if (y == height - 2) y -= 1;

    for (int i = y; i < y + 2; ++i) {
        for (int j = x; j < x + 2; ++j) {
            auto& cell = field.getCell(j,i);
            if (cell.getStatus() == Status::Occupied) {
                int index = cell.getIndexOfSegment();
                if (cell.getPointerToShip()->getSegmentState(index) != SegmentState::Destroyed){
                    flag = true;
                }
            }
        }
    }
    if (flag) {
        return AbilityResult::ShipDetected;
    }
    return AbilityResult::ShipNotDetected;
}
