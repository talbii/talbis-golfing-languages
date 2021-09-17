# talbi's yasbl Documentation

*functions labeled as `^` are **safe functions** and cannot throw an exception.*

## Arithmetic Functions

### Add

**Syntax:** `+`

**Arguments:** `x, y` (2)

**Returns:** `x + y`

### Sum^

**Syntax:** `⊕`

**Arguments:** None. (0); program_stack

**Returns:** Sums program_stack. If program_stack is empty, it will append 0.

### SumAlternating^

**Syntax:** `±`

**Arguments:** None. (0); program_stack

**Returns:** Sums program_stack, with alternating signs (that is, `+elem0-elem1+elem2-...`). If program_stack is empty, it will append 0.

### SumSquare^

**Syntax:** `⊞`

**Arguments:** None. (0); program_stack

**Returns:** Returns the sum of program_stack, squared. If program_stack is empty, it will append 0.
