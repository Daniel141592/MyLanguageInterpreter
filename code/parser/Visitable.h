#ifndef CODE_VISITABLE_H
#define CODE_VISITABLE_H

#include "Visitor.h"

class Visitable {
public:
    virtual ~Visitable() = default;

    virtual void accept(Visitor& visitor) const = 0;
};

#endif //CODE_VISITABLE_H
