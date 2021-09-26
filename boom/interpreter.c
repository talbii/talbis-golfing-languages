//
// Boom
// 26-September-2021
//

/*
Boom is a simplified language. In fact, it is so simple that you already wrote a valid program in boom:
"" (empty string)
... which is the only valid one. A program with any characters will throw a syntax error.

The empty program will halt :)
==============================
Features of Boom:
- Simplified, and easy to learn
- Robust, a syntactically correct program will never throw an exception, or access illegal memory, or create a stack overflow, etc.
- Easy to implement. 
    - infact, so easy that a Boom interpreter is almost portable; even without a compiler.
- Small program size: a valid program takes exactly 0 bytes of your drive space.
*/

__attribute__((noreturn)) void Halt(void);

#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc == 1) { // just make sure I don't access argv[1]
        puts("[Boom] Interpreting implicit empty source file.");
        Halt();
    }

    FILE* file = fopen(argv[1], "r");

    if(file == NULL) {
        puts("[Boom] Error opening file.");
        return 1;
    }

    char c;

    while((c = fgetc(file)) != EOF) {
        // if we are here then the input program has characters, which is invalid.
        printf("[Boom] Invalid syntax: character `%c` at Line 1:1\n>    Perhaps try an empty program instead?", c);
        return 1;
    }

    fclose(file);

    Halt();

    return 0;
}

__attribute__((noreturn)) void Halt(void) {
    for(;;) {}
}