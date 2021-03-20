//File: populateInfixQ.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog9
//Modified: 03/10/21

/*
Description:
This function will parse the user input into tokens and put them into the infixQ
*/


#include "../prototypes.h"
#include <iostream>


//Precondition: An empty infixQ queue of tokens and a Token of user input, probably stored as an array
//Postconditon: The infixQ queue is populated with tokens in the order of the infix expression and
//				any invalid tokens will stop tokens from being read
void populateInfixQ(Token userInput, queueType<Token>& infixQ)
{
	bool keepLooping = true;
	do //start reading tokens from input
	{
		if(userInput.Valid())// || (userInput.IsOperator() && userInput.Operator() == '-')) //add a token if it's valid
		{
			infixQ.addQueue(userInput);
			if(cin.peek() == '\n') //remove dangling newlines that cause unexpected input in the buffer and stop reading
			{
				cin.ignore(1000,'\n');
				keepLooping = false;
			}
			else //read a new token
			{
				cin >> userInput;
			}	
		}
		else //token isn't valid, stop reading and remove characters from the buffer.
		{
			keepLooping = false;
			cin.ignore(1000,'\n');
		}
	} while (keepLooping);
	//infixQ.deleteQueue(); //remove the dummy 0 token, which is used for recognizing leading operators
}