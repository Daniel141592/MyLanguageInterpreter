#include "MultiplicativeVisitor.h"

MultiplicativeVisitor::MultiplicativeVisitor(Value &v, MultiplicativeType at, std::function<void(ErrorType)> onError)
        : type(at), result(v),
          errorHandler(std::move(onError)) {};
