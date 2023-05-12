#ifndef CODE_IDENTIFIER_H
#define CODE_IDENTIFIER_H


#include <string>

#include "Factor.h"

class Identifier : public Factor {
    std::string name;
public:
    Identifier(Position p, std::string n);
    ~Identifier() override = default;

    std::string getName() const;

    void accept(const Visitor* visitor) const override;
};


#endif //CODE_IDENTIFIER_H
