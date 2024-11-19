#ifndef OOP_LAB2_ABILITYBUILDER_H
#define OOP_LAB2_ABILITYBUILDER_H
#include "Ability.h"
enum class AbilityType {
    DoubleDamage,
    Scanner,
    Bombardment
};

class AbilityBuilder {
public:
    virtual std::unique_ptr<Ability> build() const = 0;

    virtual AbilityType getType() const = 0;

    virtual void setCoords(int x, int y) = 0;

    virtual void printInfo() = 0;

    virtual ~AbilityBuilder() = default;
};
#endif //OOP_LAB2_ABILITYBUILDER_H
