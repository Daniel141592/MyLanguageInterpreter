#include "MyLangInterpreter.h"

#include <utility>

MyLangInterpreter::MyLangInterpreter(Program p, std::ostream &o, std::istream &i,
                                     MyLangInterpreter::HandlerType& onError)
                                        : program(std::move(p)), os(o), is(i), errorHandler(onError){

}
