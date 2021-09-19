#ifndef __STACKFUCK_H_
#define __STACKFUCK_H_
#include <stack> // for program stack
#include <map>

class StackfuckFunc {
public:
    virtual ~StackfuckFunc() {}
    virtual void operator() (Interpreter& i) const = 0;
};

class Interpreter {
private:
    friend class StackfuckFunc;
    std::stack<long> program_stack;
public:
    static const std::map<char, StackfuckFunc*> DefinedFunctions;
    ~Interpreter() { delete[] funcs; }

    void run_command(char); 
};

#endif // __STACKFUCK_H_