#ifndef __Stackfuck_Exceptions_H
#define __Stackfuck_Exceptions_H
#include <exception>
#include <cstring>
#include <iostream>
// Message Template:
// "*** Stackfuck: invalid functor `?`.  Terminating..."
// (of length 51, +1 for \0)

class InvalidFunctor : public std::exception {
private:
    char msg[52];
public:
    InvalidFunctor(const char *msg) {
        std::memcpy(this->msg, msg, 52);
    }
    virtual ~InvalidFunctor() = default;
    virtual const char* what() const noexcept override {
        return msg;
    }
};

#endif // __Stackfuck_Exceptions_H