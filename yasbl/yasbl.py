# -*- coding: utf-8 -*-
# yet another stack based language (yasbl)
# version. 0.0
#    date. 13 Sept 2021

"""
talbi's yet another stack based language (yasbl)

Please, refer to /yasbl/docs.md for documentation on available functions.
------
1  Base

yasbl follows a simple model that many programming languages also use: store variables in a stack.
For example, the program:
5 3 2 1
will make the stack look like [5, 3, 2, 1]. Say we now add:
5 3 2 1⊞
this will modify the stack, such that it looks like [121].

2  Interaction with the Stack
In yasbl there are 2 ways to modify the stack:
- By adding numbers to it (via a number list)
- By running functions on the existing stack
"""

from abc import ABC, abstractmethod, abstractproperty
import typing
import sys


'''class YASBLCommand(ABC):
    """ single valid YASBL command """

    @abstractmethod
    def run(self, stack: typing.List[float, str]) -> None:
        """ run a YASBL command. """

    @abstractproperty
    def symbol(self) -> str:
        """ returns this command's symbol. """

class AddCommand(YASBLCommand):
    def run(self, stack):
        if(len(stack) < 2): # "function Add+ missing arguments; got {len(self.program_stack)} but expected 2."
            YASBL.InsufficientArguments(self, len(stack), 2)
    @property
    def symbol(self):
        return "+"'''

class YASBL:
    """ YASBL running program """

    class YASBLException(Exception):
        ''' YASBL base exception '''

    class IllegalFunction(YASBLException):
        ''' Thrown when an unknown function is called. '''
        def __init__(self, message):
            super().__init__(f"unknown function {message!r}.")
    
    class InsufficientArguments(YASBLException):
        ''' Thrown when a function doesn't have enough arguments (the stack is missing some values.) '''

    def __init__(self):
        self.program_stack = []
        self.current_arg = ""
        self.funcs = {
            " ": self.Argend,
            "+": self.Add,
            "⊕": self.Sum,
            "±": self.SumAlternating,
            "S": self.SumSquare,

            "-": self.Unaryminus,
            "—": self.Stackminus,
        }

    def run(self, char: str) -> None:
        if(char != " "):
            self.current_arg += char
            self.__run_func(char)
        else:
            self.Argend()
    
    def __run_func(self, char: str) -> None:
        try:
            self.funcs[char]()
        except KeyError: # doesn't exist
            raise YASBL.IllegalFunction(char)
        # automatically raises InsufficientArguments to main.
    
    @staticmethod
    def __check_num(char: str):
        try:
            float(char)
            return True
        except ValueError:
            return False

    def Argend(self):
        if(self.__check_num(self.current_arg)):
            self.program_stack.append(float(self.current_arg))
        else:
            self.__run_func(self.current_arg)
        self.current_arg = ""

    """ --- Functions --- """
    def Add(self):
        if(len(self.program_stack) < 2):
            raise YASBL.InsufficientArguments(f"function Add+ missing arguments; got {len(self.program_stack)} but expected 2.")

    def Sum(self):
        stack_sum = sum(self.program_stack)
        del self.program_stack
        self.program_stack = [stack_sum]
    
    def SumAlternating(self):
        stack_sum: int = 0
        i = 1
        for j in self.program_stack:
            stack_sum += i*j
            i = ~(i^1)

        del self.program_stack
        self.program_stack = [stack_sum]

    def SumSquare(self):
        print("In SumSquare")
        self.Sum()
        self.program_stack[0] **= 2

    def Unaryminus(self):
        self.program_stack.append(-self.program_stack.pop())
    
    def Stackminus(self):
        self.program_stack = [-m for m in self.program_stack]
        

'''class YASBLInterpreter:
    """ Interpreter for talbi's YASBL. """

    def __init__(self):
        self.runner = YASBL()
    
    def push_symbol(self, cmd: str) -> None:
        try:
            self.runner.run(cmd)
        except YASBL.IllegalFunction as e:
            print(f"Illegal function: {e}")
        except YASBL.InsufficientArguments as e:
            print(f"Insufficient arguments: {e}")

    def run_next_command(self):
        pass

    def __bool__(self):
        pass

    def seek_number(self):
        pass'''

if(__name__ == "__main__"):
    #with open(sys.argv[1]) as f:
    with open("c:\\users\\talbi\\onedrive\\development\\talbis-golfing-languages\\yasbl\\program.tyasbl", encoding="UTF-8") as f:
        data = f.read().replace("\n", "").replace("\t", "")
    
    intrp = YASBL()

    for c in data:
        try:
            intrp.run(c)
        except Exception as e:
            print(repr(e))
    print(f"\n{intrp.program_stack}")
