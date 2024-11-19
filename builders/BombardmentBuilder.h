#ifndef OOP_LAB2_BOMBARDMENTBUILDER_H
#define OOP_LAB2_BOMBARDMENTBUILDER_H

#include "AbilityBuilder.h"
#include "Bombardment.h"


class BombardmentBuilder : public AbilityBuilder {
public:
    void setCoords(int, int) override;

    std::unique_ptr<Ability> build() const override;

    void printInfo() override;

    AbilityType getType() const override;
};


#endif //OOP_LAB2_BOMBARDMENTBUILDER_H
