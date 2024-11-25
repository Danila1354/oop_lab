#include "ScannerBuilder.h"


std::shared_ptr<Ability> ScannerBuilder::build(InfoHolder &info_holder) const {
    CoordHolder &coord_holder = info_holder.coord_holder;
    coord_holder.readCoords();
    auto[x,y] = coord_holder.get_coords();
    return std::make_shared<Scanner>(x, y, info_holder.field);
}

std::string ScannerBuilder::getAbilityName() const {
    return "Scanner";
}
