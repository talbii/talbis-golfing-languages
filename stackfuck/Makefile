source_files = interpreter.cpp main.cpp
args = -Wall -std=c++11 -c
dir = .stackfuck
compiler=g++

ifeq ($(OS),Windows_NT)
	CLEANC = del /Q /S *.o
else
	CLEANC = rm -f *.o
endif

all: build_main clean

build_main: interpreter.o main.o
	$(compiler) *.o -o stackfuck

main.o:
	$(compiler) $(args) main.cpp -o main.o

interpreter.o:
	$(compiler) $(args) interpreter.cpp -o interpreter.o

clean:
	$(CLEANC)