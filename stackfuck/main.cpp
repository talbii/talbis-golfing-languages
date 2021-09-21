#include "interpreter.h"
#include <iostream>   // for cerr, cout
#include <fstream>    // for fstream
#include <sys/stat.h> // for posix stat(); check if supplied file exists.
#include <stdio.h>

inline bool ignore_char(char);

int main(int argc, char *argv[]) {
    
    if(argc < 2) {
        std::cerr << "*** Stackfuck: Insufficient arguments (supplied " << argc << ").  Terminating..\n";
        return 1;
    }

    {
        struct stat buffer;   
        if (stat (argv[1], &buffer) != 0) {
            std::cerr << "*** Stackfuck: File at path " << argv[1] << " does not exist.  Terminating..\n";
            return 1;
        }
    }

    Interpreter i;

    std::ifstream file(argv[1]); // file should be good.

    if(!file.good()) { // this should never enter.
        std::cerr << "*** Stackfuck: Unknown error reading file.  Terminating..\n";
        return 1;
    }

    char c;
    while (file >> std::noskipws >> c) {
        if(!ignore_char(c)) {
            try{
                i.run_command(c);
            } catch(const InvalidFunctor& e) {
                printf("%s\n", e.what());
                return 1;
            }
        }
    }

    if(c != 'O' && c != 'o') {
        i.end_program();
    }

    return 0;
}

inline bool ignore_char(char c) {
    return (
        c == ' '  ||
        c == '\n' ||
        c == '\t'
    );
}