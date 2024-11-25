#ifndef OOP_LAB2_BOMBARDMENTBUILDER_H
#define OOP_LAB2_BOMBARDMENTBUILDER_H

#include "AbilityBuilder.h"
#include "Bombardment.h"
#include "CoordHolder.h"


class BombardmentBuilder : public AbilityBuilder {
public:
    std::shared_ptr<Ability> build(InfoHolder &info_holder) const override;
    std::string getAbilityName() const override;
};


#endif //OOP_LAB2_BOMBARDMENTBUILDER_H
