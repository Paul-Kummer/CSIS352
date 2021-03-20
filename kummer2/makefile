#File: makefile
#Name: Paul Kummer
#Class: CSIS 352
#Program: prog2
#Modified: 1/22/21


EXE = prog2
CC = g++
REMOVABLE_OBJS = main.o
PERM_OBJS =
OBJECTS = $(REMOVABLE_OBJS) $(PERM_OBJS)
LFLAGS =
CFLAGS =

$(EXE):							$(OBJECTS)
									$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS)

main.o:							main.cpp deque.h
									$(CC) $(CFLAGS) -c main.cpp					

clean:
									rm -rf $(EXE) $(REMOVABLE_OBJS) *~

test:
									$(EXE) < test.txt