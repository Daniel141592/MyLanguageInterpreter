#include "AdditiveVisitor.h"

AdditiveVisitor::AdditiveVisitor(Value &v, AdditiveType at, std::function<void(ErrorType)> onError)
                                                : type(at), result(v), errorHandler(std::move(onError)) {};