# Stackfuck - the greatest language, yet

Have you ever wanted to program in *Brainfuck*, but using a stack instead? Well, today your wish has been granted.

## Valid functions

In the core interpreter, there are only a handful of valid functions. Borrowing from TCL, the following functions are valid:

### Add+

Increment the top element in the stack.

### Subtract-

Decrement the top element in the stack.

### Push_next>

Push a new element (0) to the stack.

*Note:* similar to Brainfuck, `>` moves to a new "cell" in the array. However, in Stackfuck this essentially pushes a new zero (and creates a new cell). In Stackfuck, you cannot move left (`<`) to a previous cell.