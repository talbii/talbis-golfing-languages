#ifndef __STACKFUCK_H_
#define __STACKFUCK_H_
#include <stack> // for program stack
#include <map>   // map of characters<->functors
#include "sfexceptions.h" // included here, so you don't need to include this in main.

class Interpreter;

class StackfuckFunc {
public:
	virtual ~StackfuckFunc() {}
	virtual void operator() (Interpreter& i) const = 0;
    std::stack<long>& get_stack(Interpreter& i) const;
};

class Interpreter {
private:
    std::stack<long> program_stack;
    static unsigned int interpreter_instances;
public:
    Interpreter() { 
        Interpreter::interpreter_instances++;
        this->program_stack.push(0);
    }
    static const std::map<char, StackfuckFunc*> DefinedFunctions;
    virtual ~Interpreter() {
        if(--interpreter_instances == 0) {
            for(auto it = Interpreter::DefinedFunctions.begin();
                it != Interpreter::DefinedFunctions.end(); it++) {
                    delete (*it).second;
                }
        }
    }
    void end_program();
    void printstack();
    void run_command(char); 
    friend class StackfuckFunc;
};

#endif // __STACKFUCK_H_