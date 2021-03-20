#File: makefile
#Name: Paul Kummer
#Class: CSIS 352
#Program: prog8
#Modified: 03/01/21

EXE = prog8
CC = g++
OBJECTS = main.o operations.o functions.o
LFLAGS =
CFLAGS =

$(EXE):							$(OBJECTS)
									$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS)

main.o:							main.cpp prototypes.h
									$(CC) $(CFLAGS) -c main.cpp

operations.o:					operations.cpp prototypes.h
									$(CC) $(CFLAGS) -c operations.cpp

functions.o:					functions.cpp prototypes.h
									$(CC) $(CFLAGS) -c functions.cpp

clean:
									rm -rf $(EXE) $(OBJECTS) *~

test:							
									$(EXE) test.txt