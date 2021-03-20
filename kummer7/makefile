#File: makefile
#Name: Paul Kummer
#Class: CSIS 352
#Program: prog7
#Modified: 02/23/21


EXE = prog7
CC = g++
OBJECTS = main.o operations.o people.o
LFLAGS =
CFLAGS =

$(EXE):							$(OBJECTS)
									$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS)

main.o:							main.cpp prototypes.h modArray.h
									$(CC) $(CFLAGS) -c main.cpp

operations.o:					operations.cpp prototypes.h modArray.h
									$(CC) $(CFLAGS) -c operations.cpp

people.o:						people.cpp prototypes.h
									$(CC) $(CFLAGS) -c people.cpp

clean:
									rm -rf $(EXE) $(OBJECTS) *~

test:							
									$(EXE) test.txt

test2:							
									$(EXE) test2.txt