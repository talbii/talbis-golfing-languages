import sys

def inf_loop() -> None:
    """ Calling this function will make the program halt. """
    while(True):
        pass

def main():
    """ Boom main implementation"""
    if(len(sys.argv) < 2):
        print("[Boom] Interpreting implicit empty source file.")
        Halt()
    try:
        with open(sys.argv[1], "r") as f:
            program = f.read()
    except FileNotFoundError:
        print("[Boom] Error opening file.")
        return
    
    if(program != ""):
        print(f"[Boom] Invalid syntax: character `{program[0]}` at Line 1:1\n>    Perhaps try an empty program instead?")
        return
    
    inf_loop()


if(__name__ == "__main__"):
    main()
