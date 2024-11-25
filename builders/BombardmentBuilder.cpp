#include "BombardmentBuilder.h"


std::shared_ptr<Ability> BombardmentBuilder::build(InfoHolder &info_holder) const {
    return std::make_shared<Bombardment>(info_holder.ship_manager);
}

std::string BombardmentBuilder::getAbilityName() const {
    return "Bombardment";
}
