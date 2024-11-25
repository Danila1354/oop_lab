#ifndef OOP_LAB2_SCANNERBUILDER_H
#define OOP_LAB2_SCANNERBUILDER_H

#include "AbilityBuilder.h"
#include "Scanner.h"

class ScannerBuilder : public AbilityBuilder {
public:
    std::shared_ptr<Ability> build(InfoHolder &info_holder) const override;
    std::string getAbilityName() const override;

};

#endif //OOP_LAB2_SCANNERBUILDER_H
