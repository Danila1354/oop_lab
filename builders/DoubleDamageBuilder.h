#ifndef OOP_LAB2_DOUBLEDAMAGEBUILDER_H
#define OOP_LAB2_DOUBLEDAMAGEBUILDER_H

#include "AbilityBuilder.h"
#include "DoubleDamage.h"

class DoubleDamageBuilder : public AbilityBuilder {
private:
    int x, y;
public:
    std::shared_ptr<Ability> build(InfoHolder &info_holder) const override;
    std::string getAbilityName() const override;
};


#endif //OOP_LAB2_DOUBLEDAMAGEBUILDER_H
