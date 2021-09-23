# Stackfuck - the greatest language, yet

Have you ever wanted to program in *Brainfuck*, but using a stack instead of an array? Well, today your wish has been granted.

- [Stackfuck - the greatest language, yet](#stackfuck---the-greatest-language-yet)
  - [Labels in this Documentation](#labels-in-this-documentation)
  - [Base Functors](#base-functors)
    - [Increment`^` +0](#increment-0)
    - [Decrement`v` +0](#decrementv-0)
    - [Push_next`>` +1](#push_next-1)
    - [Input`I` +0](#inputi-0)
    - [Input`i` +0](#inputi-0-1)
    - [Output`O` +0](#outputo-0)
    - [Output`o` +0](#outputo-0-1)
    - [Pop`!`(!) -1](#pop--1)
  - [Stack Functors](#stack-functors)
    - [Add`+`(!) -1](#add--1)
    - [Subtract`-`(!) -1](#subtract---1)
    - [Multiply`*`(!) -1](#multiply--1)
    - [Divide`/`(!) -1](#divide--1)
  - [Running the Interpreter](#running-the-interpreter)
  - [Extending Stackfuck](#extending-stackfuck)

## Labels in this Documentation

- Functors labeled using __!__ are labeled as *unsafe*, meaning they may crash your program.
- Each functor has a `+/-N` after its name. This indicates by how much elements the functor modifies the stack. For example, `Push_next` is +1 and `Pop` is -1. Additionally, a `z` may be added to indicate that this functor zeroes the current element.

## Base Functors

In the core interpreter, there are only a handful of valid functions. Borrowing from TCL, the following functions are valid:

### Increment`^` +0

Increment the top element in the stack.

### Decrement`v` +0

Decrement the top element in the stack.

### Push_next`>` +1

Push a new element (0) to the stack.

*Note:* similar to Brainfuck, `>` moves to a new "cell" in the array. However, in Stackfuck this essentially pushes a new zero (and creates a new cell). In Stackfuck, you cannot move left (`<`) to a previous cell.

Checkout section [Modifying the Stack](#stack-functors) to learn about modifying the stack.

### Input`I` +0

Gets a single character from the user and puts its ASCII value in the stack.

### Input`i` +0

Gets a single character from the user. If it is a numeric value (that is, between `'0'` and `'9'`) then the numeric value will be pushed to the stack. Otherwise, an error will be thrown.

### Output`O` +0

Outputs the top element in the stack according to its ASCII character.

### Output`o` +0

Outputs the top element in the stack, literally.

### Pop`!`(!) -1

Pops the current element from the stack.

## Stack Functors

These functors allow you to *actually* modify the stack, that is, a Stack functor can push/pop elements according to its functionality.

### Add`+`(!) -1

- Adds the top two elements in the stack.
- *Pops the top two elements, and pushes the result instead.*

Throws an exception when the stack is missing elements.

### Subtract`-`(!) -1

- Subtracts the top two elements in the stack.
- *Pops the top two elements, and pushes the result instead.*

Throws an exception when the stack is missing elements.

### Multiply`*`(!) -1

- Multiplies the top two elements in the stack.
- *Pops the top two elements, and pushes the result instead.*

Throws an exception when the stack is missing elements.

### Divide`/`(!) -1

- Divides the top two elements in the stack.
- *Pops the top two elements, and pushes the result instead.*

Throws an exception when the stack is missing elements.

## Running the Interpreter

Supplied is a Makefile, for you to compile yourself. I'll assume that you have some knowledge on how to build projects yourself. Simply, run `make` while in the directory `stackfuck/` and, (assuming you have `g++`) you will get out the *official* Stackfuck interpreter!

To run, simply type:

```shell
$ stackfuck [path_to_source_file]
```

If you have a different compiler, modify Line 4 in the file, and change `g++` to whatever compiler you have (for example, `clang`).

## Extending Stackfuck

I designed this project to be modular, so adding new functors is very simple.

*This section has moved to [extending Stackfuck](extending-stackfuck.md)*.
