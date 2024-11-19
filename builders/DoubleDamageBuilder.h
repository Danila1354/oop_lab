#ifndef OOP_LAB2_DOUBLEDAMAGEBUILDER_H
#define OOP_LAB2_DOUBLEDAMAGEBUILDER_H

#include "AbilityBuilder.h"
#include "DoubleDamage.h"

class DoubleDamageBuilder : public AbilityBuilder {
private:
    int x, y;
public:
    void setCoords(int x, int y) override;

    std::unique_ptr<Ability> build() const override;

    void printInfo() override;

    AbilityType getType() const override;
};


#endif //OOP_LAB2_DOUBLEDAMAGEBUILDER_H
