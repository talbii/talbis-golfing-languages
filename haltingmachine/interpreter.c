//
// HaltingMachine
// 28-September-2021
//

/*
HaltingMachine is a very basic (and pointless) Esolang. It is essentially a fork of Boom.
As such, I am lazy and have copied the file "/boom/interpreter.c" to this file.
The available functions are:
- H(ello World): print "Hello World!\n"
- Q(uine): Print Source Program
- F(izz Buzz): FizzBuzz upto (n), where n is the value of the Accumulator! this also resets the Accumulator.
- +: Increment the Accumulator.
    - *: Multiply the Accumulator by a random number (2, chosen randomly using a dice roll; guranteed to be random)
    - ^: Power the accumulator by 2 (square it)
- !(!!!): Run forever (infinite loop).
an empty program is guranteed to halt, because that can be useful?

-- Yes, this is inspired (heavily) by HQ9+.

*/

__attribute__((noreturn)) void Halt(void);
char* get_program(const char*);
void fizzbuzz(void);


#include <stdio.h>
#include <stdlib.h>

unsigned long long accumulator = 0;

int main(int argc, char *argv[]) {
    if(argc == 1) { // just make sure I don't access argv[1]
        puts("[HaltingMachine] Interpreting implicit empty source file.");
        inf_loop();
    }

    FILE* file = fopen(argv[1], "r");

    if(file == NULL) {
        puts("[HaltingMachine] Error opening file.");
        return 1;
    }

    char *program = get_program(argv[1]);

    char c;
    size_t i = 1, line_counter = 1;

    while((c = fgetc(file)) != EOF) {
        switch(c) {
            case 'H':
                puts("Hello World!");
                break;
            case 'Q':
                puts(program);
                break;
            case 'F':
                fizzbuzz();
                break;
            case '+':
                accumulator++;
                break;
            case '*':
                accumulator *= 2;
                break;
            case '^':
                accumulator *= accumulator;
                break;
            case '!':
                fclose(file);
                free(program);
                inf_loop();              
                break;
            case ' ' :
            case '\t':
                break;
            case '\n':
                line_counter++;
                i = 1;
            default:
                printf("[HaltingMachine] Invalid syntax: character `%c` at Line %d:%d\n>    Perhaps try an empty program instead?", c);
                return 1;
        }

        i++;
    }

    if(i == 1 && line_counter == 1) {
        fclose(file);
        free(program);
        inf_loop(); // empty program!
    }

    fclose(file);
    free(program);

    return 0;
}

__attribute__((noreturn)) void inf_loop(void) {
    for(;;) {}
}

char* get_program(const char* path) {
    FILE* file = fopen(path, "rb");

    if(file == NULL) {
        puts("[HaltingMachine] Error opening file for function Quine. Note- (Q)uine may result in garbage output.");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *file_txt = malloc(fsize + 1);

    if(!file_txt) {
        puts("[HaltingMachine] Error allocating memory for function Quine. Note- (Q)uine may result in garbage output.");
        return NULL;
    }

    fread(file_txt, 1, fsize, file);
    fclose(file);

    file_txt[fsize] = '\0';

    return file_txt; 
}

void fizzbuzz(void) {
    if(accumulator < 0) {
        puts("[HaltingMachine] Oh oh! you've overflowed the Accumulator! I am going to halt now.");
        Halt();
    }

    unsigned long long i = 1;

    for(;
        i <= accumulator - 1; ++i) {
                 if(i % 15 == 0) fputs("Fizz Buzz, ", stdout);
            else if(i % 5  == 0) fputs("Buzz, ", stdout);
            else if(i % 3  == 0) fputs("Fizz, ", stdout);
            else                 printf("%llu, ", i);
        }
               if(i % 15 == 0) puts("Fizz Buzz");
            else if(i % 5  == 0) puts("Buzz");
            else if(i % 3  == 0) puts("Fizz");
            else                 printf("%llu\n", i);

    accumulator = 0;
}
