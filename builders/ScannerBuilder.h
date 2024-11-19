#ifndef OOP_LAB2_SCANNERBUILDER_H
#define OOP_LAB2_SCANNERBUILDER_H

#include "AbilityBuilder.h"
#include "Scanner.h"

class ScannerBuilder : public AbilityBuilder {
private:
    int x, y;
public:
    void setCoords(int x, int y) override;

    std::unique_ptr<Ability> build() const override;

    void printInfo() override;

    AbilityType getType() const override;
};

#endif //OOP_LAB2_SCANNERBUILDER_H
