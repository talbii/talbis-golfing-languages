# Stackfuck - the greatest language, yet

Have you ever wanted to program in *Brainfuck*, but using a stack instead? Well, today your wish has been granted.

## Base Functors

In the core interpreter, there are only a handful of valid functions. Borrowing from TCL, the following functions are valid:

### Increment`^`

Increment the top element in the stack.

### Decrement`v`

Decrement the top element in the stack.

### Push_next`>`

Push a new element (0) to the stack.

*Note:* similar to Brainfuck, `>` moves to a new "cell" in the array. However, in Stackfuck this essentially pushes a new zero (and creates a new cell). In Stackfuck, you cannot move left (`<`) to a previous cell.

Checkout section [Modifying the Stack](#stack-functors) to learn about modifying the stack.

### Input`I`

Gets a single character from the user and puts its ASCII value in the stack.

### Input`i`

Gets a single character from the user. If it is a numeric value (that is, between `'0'` and `'9'`) then the numeric value will be pushed to the stack. Otherwise, an error will be thrown.

### Output`O`

Outputs the top element in the stack according to its ASCII character.

### Output`o`

Outputs the top element in the stack, literally.

## Stack Functors

These functors allow you to *actually* modify the stack, that is, a Stack functor can push/pop elements according to its functionality.
