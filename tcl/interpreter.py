# talbi's Turing Complete Language
# version. 0.2
#    date. 12 Sept 2021

"""
talbi's TC language (operators)

1  Base Operators
+: increment current cell
-: decrement current cell
>: move (+1) cell
<: move (-1) cell

2  IO

O: output current cell as ASCII
I: input to current cell (gets a single char)

3  Branch control
[: if current cell is zero
]: endif
{: while current cell is nonzero
}: endwhile

4  Misc. Operations

z: zero current cell
"...": comments
"""

import re

class TCLObject:

    """ Represents a single (running) program. """


    
    class IllegalCellAccess(Exception):
        """ thrown when cell -1 is being accessed. """
        def __init__(self, desc: str):
            self.description = desc
        def describe(self) -> str:
            return self.description

    
    def __init__(self): 
        self.operators = {
            "+": self._incrementcell,
            "-": self._decrementcell,
            ">": self._moveicell,
            "<": self._movedcell,
            "O": self._printcell,
            "I": self._inputcell,
            "[": self._if,
            "]": self._endif,
            "{": self._while,
            "}": self._endwhile,
            "z": self._zerocell,
        }
        self.cells = [0]
        self.current_cell = 0
        self.ignore_mode = False
    def do_operation(self, char: str) -> bool:
        if(self.ignore_mode):
            return True
        try:
            self.operators[char]()
        except KeyError:
            print(f"Unknown operator {char}.")
            return False
        except TCLObject.IllegalCellAccess as e:
            print(e.describe())
        return True

    def _modcell(self, x: int) -> None: 
        self.cells[self.current_cell] += x
    
    def _incrementcell(self) -> None: self._modcell(1)
    def _decrementcell(self) -> None: self._modcell(-1)
    
    def _moveicell(self) -> None:
        self.current_cell += 1
        if(len(self.cells) == self.current_cell): self.cells.append(0)
        
    def _movedcell(self) -> None:
        self.current_cell -= 1
        if(self.current_cell < 0):
            raise TCLObject.IllegalCellAccess("error: cannot access cell -1.\n\t Exiting...")
    
    def _printcell(self) -> None:
        print(chr(self.cells[self.current_cell]), end="")
    
    def _inputcell(self) -> None:
        self.cells[self.current_cell] = ord(input()[0])

    def _zerocell(self) -> None:
        self.cells[self.current_cell] = 0

    @property
    def Get(self) -> int:
        return self.cells[self.current_cell]

    def _if(self) -> None:
        if(self.Get != 0):
            self.ignore_mode = True
    
    def _endif(self) -> None:
        self.ignore_mode = False

    def _while(self):
        if(self.Get == 0):
            self.ignore_mode = True

    def _endwhile(self):
        self.ignore_mode = False
    
    @staticmethod
    def run_file(file_path: str):
        with open(file_path) as f:
            data = f.read().strip().replace("\n", "").replace("\t", "").replace(" ", "")
            data = re.sub(r'\"(.*?)\"', "", data)
        
        o: TCLObject = TCLObject()
        increment: bool = True

        i: int = 0

        branch_begins = []

        while True:
            if(data[i] == "{"):
                branch_begins.append(i)

            if(data[i] == "}"):
                o.do_operation(data[i])
                if(o.Get != 0): # not zero, continue while
                    i = branch_begins.pop()
                    increment = False
                else:
                    i += 1

            if(not o.do_operation(data[i])): return # Exit if do_operations returns False (= error occurred.)
            
            if(increment):
                i += 1
            else:
                increment = True

            if(i == len(data)): break

if(__name__ == "__main__"):
    TCLObject.run_file(input("Enter file path: "))