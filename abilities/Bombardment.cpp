#include "Bombardment.h"

bool Bombardment::apply(GameField &field) {
    std::vector<std::pair<int, int>> attackable_segments;
    for (int y = 0; y < field.getHeight(); ++y) {
        for (int x = 0; x < field.getWidth(); ++x) {
            auto &cell = field.getCell(x, y);
            auto *pointer_to_ship = cell.getPointerToShip();
            if (pointer_to_ship != nullptr &&
                pointer_to_ship->getSegmentState(cell.getIndexOfSegment()) != SegmentState::Destroyed) {
                attackable_segments.emplace_back(x, y);
            }
        }
    }
    if (attackable_segments.empty()) {
        return false;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, attackable_segments.size() - 1);
    auto [target_x, target_y] = attackable_segments[dist(gen)];
    auto &target_cell = field.getCell(target_x, target_y);
    auto *target_ship = target_cell.getPointerToShip();
    auto index = target_cell.getIndexOfSegment();
    target_ship->takeDamage(index);
    if (target_ship->isShipDestroyed()){
        if (target_ship->isVertical()){
            for (int y = target_y-index;y<target_y-index+target_ship->getLength();y++){
                field.getCell(target_x,y).open();
            }
        }
        else{
            for (int x = target_x-index;x<target_x-index+target_ship->getLength();x++){
                field.getCell(x,target_y).open();
            }
        }
    }
    return target_ship->isShipDestroyed();
}