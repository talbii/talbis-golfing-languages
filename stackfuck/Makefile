source_files = interpreter.cpp main.cpp
args = -Wall -std=c++11 -c
dir = .stackfuck

ifeq ($(OS),Windows_NT)
	CLEANC = del /Q /S *.o
else
	CLEANC = rm -f *.o
endif

all: build_main clean

build_main: interpreter.o main.o
	g++ *.o -o stackfuck

main.o:
	g++ $(args) main.cpp -o main.o

interpreter.o:
	g++ $(args) interpreter.cpp -o interpreter.o

clean:
	$(CLEANC)