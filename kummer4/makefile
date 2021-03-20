#File: makefile
#Name: Paul Kummer
#Class: CSIS 352
#Program: prog4
#Modified: 01/29/21


EXE = prog4
CC = g++
OBJECTS = main.o
LFLAGS =
CFLAGS =

$(EXE):							$(OBJECTS) array.h
									$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS)

main.o:							main.cpp
									$(CC) $(CFLAGS) -c main.cpp

clean:
									rm -rf $(EXE) $(OBJECTS) *~

test:							
									$(EXE) test.txt