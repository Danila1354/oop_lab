#include "DoubleDamageBuilder.h"

void DoubleDamageBuilder::setCoords(int x, int y) {
    this->x = x;
    this->y = y;
}

std::unique_ptr<Ability> DoubleDamageBuilder::build() const {
    return std::make_unique<DoubleDamage>(x, y);
}

AbilityType DoubleDamageBuilder::getType() const {
    return AbilityType::DoubleDamage;
}

void DoubleDamageBuilder::printInfo(){
    std::cout<<"Double damage ability is applied"<<'\n';
}