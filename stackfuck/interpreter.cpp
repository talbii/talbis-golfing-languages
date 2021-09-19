#include "interpreter.h"
#include <stdio.h>

namespace stackfuck_builtin {
    class Add : public StackfuckFunc {
    public:
        virtual void operator() (Interpreter& i) const {
            i.program_stack.top()++;
        }
    };

    class Subtract : public StackfuckFunc {
    public:
        virtual void operator() (Interpreter& i) const {
            i.program_stack.top()--;
        }
    };

    class Push_next : public StackfuckFunc {
    public:
        virtual void operator() (Interpreter& i) const {
            i.program_stack.push(0);
        }
    };

    class Input : public StackfuckFunc {
    public:
        virtual void operator() (Interpreter& i) const {
            i.program_stack.push(getchar());
        }
    };

    class InputNumeric : public StackfuckFunc {
    public:
        virtual void operator() (Interpreter& i) const {
            char c = getchar();
            if(c >= '0' && c <= '9') {
                i.program_stack.push(c - '0');
            } else {
                puts("Error! Non-numeric value entered!");
                exit(1); 
            }
        }
    };

    class Output : public StackfuckFunc {
    public:
        virtual void operator() (Interpreter& i) const {
            putchar(i.program_stack.top());
        }
    };

    class Output : public StackfuckFunc {
    public:
        virtual void operator() (Interpreter& i) const {
            printf("%ld", i.program_stack.top());
        }
    };
}

Interpreter::DefinedFunctions = {
    {'^', stackfuck_builtin::Add()}
};