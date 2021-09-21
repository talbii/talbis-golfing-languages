#ifndef __Stackfuck_BASEFUNCTORS_H
#define __Stackfuck_BASEFUNCTORS_H

#include "interpreter.h"
#include <stdio.h>

class Increment : public StackfuckFunc {
public:
    virtual void operator() (Interpreter& i) const {
        get_stack(i).top()++;
    }

    virtual void whoami() const {
        std::cout << "Increment\n";
    }
};

class Decrement : public StackfuckFunc {
public:
    virtual void operator() (Interpreter& i) const {
        get_stack(i).top()--;
    }
};

class Push_next : public StackfuckFunc {
public:
    virtual void operator() (Interpreter& i) const {
        get_stack(i).push(0);
    }
};

class Input : public StackfuckFunc {
public:
    virtual void operator() (Interpreter& i) const {
        get_stack(i).push(getchar());
    }
};

class InputNumeric : public StackfuckFunc {
public:
    virtual void operator() (Interpreter& i) const {
        char c = getchar();
        if(c >= '0' && c <= '9') {
            get_stack(i).push(c - '0');
        } else {
            puts("Error! Non-numeric value entered!");
            exit(1);
        }
    }
};

class Output : public StackfuckFunc {
public:
    virtual void operator() (Interpreter& i) const {
        putchar(get_stack(i).top());
    }
};

class OutputLiteral : public StackfuckFunc {
public:
    virtual void operator() (Interpreter& i) const {
        printf("%ld", get_stack(i).top());
    }
};

#endif // __Stackfuck_BASEFUNCTORS_H