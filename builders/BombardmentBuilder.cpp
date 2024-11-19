#include "BombardmentBuilder.h"

void BombardmentBuilder::setCoords(int, int) {}

std::unique_ptr<Ability> BombardmentBuilder::build() const {
    return std::make_unique<Bombardment>();
}

AbilityType BombardmentBuilder::getType() const {
    return AbilityType::Bombardment;
}
void BombardmentBuilder::printInfo() {
    std::cout<<"Bombardment ability is applied"<<'\n';
}