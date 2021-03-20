//File: populateInfixQ.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog1
//Modified: 01/15/21

/*
Description:
This function will parse the user input into tokens and put them into the infixQ
*/


#include "../prototypes.h"
#include <iostream>


//Precondition: An empty infixQ queue of tokens and a Token of user input, probably stored as an array
//Postconditon: The infixQ queue is populated with tokens in the order of the infix expression
void populateInfixQ(Token userInput, queueType<Token>& infixQ)
{
	//continuously place tokens on the back of the queue until a token is invalid
	while(userInput.Valid())
	{
		infixQ.addQueue(userInput);
		cin >> userInput;
	}
}