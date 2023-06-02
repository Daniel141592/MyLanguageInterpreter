#ifndef CODE_STANDARDOUTPUT_H
#define CODE_STANDARDOUTPUT_H

#include <iostream>
#include <sstream>
#include "SingleInstruction.h"
#include "../interpreter/Value.h"
#include "../interpreter/Aliases.h"

class StandardOutput : public SingleInstruction {
    std::ostream& os;
public:
    explicit StandardOutput(std::ostream& o);

    void accept(Visitor &visitor) const override;
    void print(const Value& value) const;
};


#endif //CODE_STANDARDOUTPUT_H
