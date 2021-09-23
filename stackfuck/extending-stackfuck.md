# Extending Stackfuck

I built the interpreter to follow as much OOP rules as I could (even though I despise this paradigm). To extend the interpreter (that is, adding more functors), you only need to modify a few values. In this guide I will show how to extend the interpreter, step by step.

*Note: you do need previous knowledge in C++*.

***

The interpreter class has looks up functors using a map, which is equivalent to all instances of the class. Unfortunately, this map is indeed `const`, so you cannot modify it.

Instead, we will create a new class, which derives from `Interpreter` and has its own map of customized functors:

```c++
class MyInterpreter : public Interpreter {
private:
    std::map<char, StackfuckFunc*> funcs;
};
```

In Stackfuck, all functors derive from the abstract class `StackfuckFunc`, which has a singular abstract method to be implemented, which is:

```c++
class MyCustomFunctor : public StackfuckFunc {
public:
    virtual void operator() (Interpreter& i) const {
        // todo.
    }
};
```

In this example, I will extend Stackfuck, by adding the functor `AddThree` which adds 3 to the top value in the stack. Its implementation is quite forward:

```c++
void AddThree::operator() (Interpreter& i) const {
    get_stack(i).top() += 3;
}
```

*note: To access the interpreter's stack (internally named program_stack) use the method `StackfuckFunc::get_stack` which, given a reference to an interpreter returns a reference to its stack*.

Okay, we've now implemented our custom functor, and we're left with adding it to our custom interpreter. To do so, we need to add the object `AddThree()` to our new map. I would implement it like this:

```c++
class MyInterpreter : public Interpreter {
private:
    std::map<char, StackfuckFunc*> funcs; // your custom functors map
public:
    void add_functor(char c, StackfuckFunc* func) {
        this->funcs[c] = func->clone();
    }

    virtual void run_command(char c) {
        try {
            this->Interpreter::run_command(c);
        } catch(const InvalidFunctor& e) { // not builtin command
            StackfuckFunc* func;
            try {
                func = this->funcs.at(c);
            } catch(std::out_of_range& e) { // functor does not exist, even in custom functor map.
                char text[] = INVALID_FUNCTOR_STR;
                text[32] = c; // access char '?'
                throw InvalidFunctor(text);
            }

            (*func)(*this);
        }
    }
};
```

and, in your main file:

```c++
int main(int argc, char* argv[]) {
    MyInterpreter i;

    i.add_functor('A', &AddThree()); // make sure 'A' is not used :)

    ...
}
```
