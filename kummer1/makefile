#File: makefile
#Name: Paul Kummer
#Class: CSIS 352
#Program: prog1
#Modified: 01/15/21


EXE = prog1
CC = g++
REMOVABLE_OBJS = main.o populateInfixQ.o populatePostfixQ.o evaluatePostFixExpression.o
PERM_OBJS = token.o
OBJECTS = $(REMOVABLE_OBJS) $(PERM_OBJS)
LFLAGS =
CFLAGS =

$(EXE):							$(OBJECTS)
									$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS)

main.o:							main.cpp prototypes.h token/token.h queue/queueType.h stack/stackType.h
									$(CC) $(CFLAGS) -c main.cpp

populateInfixQ.o:				functions/populateInfixQ.cpp prototypes.h
									$(CC) $(CFLAGS) -c functions/populateInfixQ.cpp

populatePostfixQ.o:				functions/populatePostfixQ.cpp prototypes.h
									$(CC) $(CFLAGS) -c functions/populatePostfixQ.cpp

evaluatePostFixExpression.o:	functions/evaluatePostFixExpression.cpp prototypes.h
									$(CC) $(CFLAGS) -c functions/evaluatePostFixExpression.cpp						

clean:
									rm -rf $(EXE) $(REMOVABLE_OBJS) *~