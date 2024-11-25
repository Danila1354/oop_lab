#ifndef OOP_LAB2_ABILITYBUILDER_H
#define OOP_LAB2_ABILITYBUILDER_H
#include "Ability.h"
#include "InfoHolder.h"

class AbilityBuilder {
public:
    virtual std::shared_ptr<Ability> build(InfoHolder &info_holder) const = 0;
    virtual std::string getAbilityName() const = 0;
    virtual ~AbilityBuilder() = default;
};
#endif //OOP_LAB2_ABILITYBUILDER_H
