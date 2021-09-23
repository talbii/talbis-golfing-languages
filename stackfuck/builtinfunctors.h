#ifndef __Stackfuck_BASEFUNCTORS_H
#define __Stackfuck_BASEFUNCTORS_H

#include "interpreter.h"
#include <stdio.h>

// ---------------------------
//       Base functors
// ---------------------------

class Increment : public StackfuckFunc {
public:
    virtual void operator() (Interpreter& i) const {
        get_stack(i).top()++;
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

class Pop : public StackfuckFunc {
public:
    virtual void operator() (Interpreter& i) const {
        get_stack(i).pop();
    }
};

// ---------------------------
//      Stack functors
// ---------------------------

/* Helper class -- In order to avoid duplicate code when implementing +,-,*,/ derive from this class and implement do_arithmetic. */
class _ArithmeticFunc : public StackfuckFunc {
public:
    virtual void operator() (Interpreter& i) const {
        std::stack<long>& s = get_stack(i);
        if(s.size() < 2) {
            char text[INSUFFICIENT_ARGUMENTS_MSG] = INSUFFICIENT_ARGUMENTS_STR;
            text[43] = '2';        // access char '?'
            text[53] = '0' + (int)s.size(); // access char '!'
            throw InsufficientArguments(text); /* note: refactor this, such that Add derives from SFFunc_Insuf, which has a method to build this error string. */
        }
        long a, b;
        a = s.top();
        s.pop();

        b = s.top();
        s.pop();

        s.push(this->do_arithmetic(a, b));
    }

    virtual long do_arithmetic(long, long) const = 0;
};

class Add : public _ArithmeticFunc {
public:
    virtual long do_arithmetic(long a, long b) const {
        return a + b;
    }
};

class Subtract : public _ArithmeticFunc {
public:
    virtual long do_arithmetic(long a, long b) const {
        return a - b;
    }
};

class Multiply : public _ArithmeticFunc {
public:
    virtual long do_arithmetic(long a, long b) const {
        return a * b;
    }
};

class Divide : public _ArithmeticFunc {
public:
    virtual long do_arithmetic(long a, long b) const {
        return a / b;
    }
};

#endif // __Stackfuck_BASEFUNCTORS_H
