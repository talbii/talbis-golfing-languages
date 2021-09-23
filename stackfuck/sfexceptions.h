#ifndef __Stackfuck_Exceptions_H
#define __Stackfuck_Exceptions_H
#include <exception>
#include <cstring>
#include <iostream>

#define INVALID_FUNCTOR_MSG 52
#define INVALID_FUNCTOR_STR "*** Stackfuck: invalid functor `?`.  Terminating..."
#define INSUFFICIENT_ARGUMENTS_MSG 72
#define INSUFFICIENT_ARGUMENTS_STR "*** Stackfuck: missing arguments, expected ? but got !.  Terminating..."

// Message Template:
// "*** Stackfuck: invalid functor `?`.  Terminating..."
// (of length 51, +1 for \0)

class sf_base_exception : public std::exception {};

class InvalidFunctor : public sf_base_exception {
private:
    char msg[INVALID_FUNCTOR_MSG] = "*** Stackfuck: invalid functor `?`.  Terminating...";
public:
    InvalidFunctor(char invalid_functor) {
        msg[32] = invalid_functor;
    }
    virtual ~InvalidFunctor() = default;
    virtual const char* what() const noexcept override {
        return msg;
    }


};

// Message Template:
// "*** Stackfuck: missing arguments, expected ? but got !.  Terminating..."

class InsufficientArguments : public sf_base_exception {
private:
    char msg[INSUFFICIENT_ARGUMENTS_MSG];
public:
    InsufficientArguments(const char *msg) {
        std::memcpy(this->msg, msg, INSUFFICIENT_ARGUMENTS_MSG);
    }

    virtual ~InsufficientArguments() = default;
    virtual const char* what() const noexcept override {
        return msg;
    }
};

#endif // __Stackfuck_Exceptions_H