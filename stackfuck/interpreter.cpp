#include "interpreter.h"
#include "basefunctors.h"
#include <stdexcept>

unsigned int Interpreter::interpreter_instances = 0;

std::stack<long>& StackfuckFunc::get_stack(Interpreter& i) const {
    return i.program_stack;
}

void Interpreter::run_command(char c) {
    StackfuckFunc *func;
    try {
        func = Interpreter::DefinedFunctions.at(c);
    } catch(std::out_of_range& e) { // functor does not exist
        char text[] = "*** Stackfuck: invalid functor `?`.  Terminating...";
        text[32] = c;
        throw InvalidFunctor(text);
    }

    (*func)(*this);
}

void Interpreter::end_program() {
    while(!program_stack.empty()) {
        printf("%ld ", program_stack.top());
        program_stack.pop();
    }
}

const std::map<char, StackfuckFunc*> Interpreter::DefinedFunctions = {
    {'^', new Increment()},
    {'v', new Decrement()},
    {'>', new Push_next()},
    {'I', new Input()},
    {'i', new InputNumeric()},
    {'O', new Output()},
    {'o', new OutputLiteral()},
};