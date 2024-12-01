#include "DoubleDamageBuilder.h"

std::shared_ptr<Ability> DoubleDamageBuilder::build(InfoHolder &info_holder) const {;
    return std::make_shared<DoubleDamage>(x,y,info_holder.field);
}

std::string DoubleDamageBuilder::getAbilityName() const {
    return "DoubleDamage";
}

