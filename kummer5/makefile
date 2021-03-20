#File: makefile
#Name: Paul Kummer
#Class: CSIS 352
#Program: prog5
#Modified: 02/09/21


EXE = prog5
CC = g++
OBJECTS = main.o operations.o
LFLAGS =
CFLAGS =

$(EXE):							$(OBJECTS)
									$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS)

main.o:							main.cpp prototypes.h modArray.h
									$(CC) $(CFLAGS) -c main.cpp

operations.o:					operations.cpp prototypes.h modArray.h
									$(CC) $(CFLAGS) -c operations.cpp

clean:
									rm -rf $(EXE) $(OBJECTS) *~

test:							
									$(EXE) test.txt