#ifndef CODE_IDENTIFIER_H
#define CODE_IDENTIFIER_H


#include <string>
#include "../Visitable.h"

class Identifier : Visitable {
    std::string name;
public:
    Identifier(std::string n);
    ~Identifier() override = default;

    std::string getName() const;

    void accept(const Visitor* visitor) const override;
};


#endif //CODE_IDENTIFIER_H
