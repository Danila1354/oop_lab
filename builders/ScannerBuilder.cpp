#include "ScannerBuilder.h"

void ScannerBuilder::setCoords(int x, int y) {
    this->x = x;
    this->y = y;
}

std::unique_ptr<Ability> ScannerBuilder::build() const {
    return std::make_unique<Scanner>(x, y);
}

AbilityType ScannerBuilder::getType() const {
    return AbilityType::Scanner;
}

void ScannerBuilder::printInfo(){
    std::cout<<"Scanner ability is applied"<<'\n';
}