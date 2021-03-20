//File: main.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog1
//Modified: 01/15/21

/*
Description:
This program will prompt the user to write infix expressions unitl the expression equals 0.
The user must enter a valid infix expression, otherwise the program will terminate. After 
entering a valid infix expression, the program will turn the string into tokens and place
them into an infix queue. Once the infix queue is filled from the input stream, the infix
queue is copied into a temporary queue. The temporary queue has each token extracted in order
and outputted to the user. Then the infix queue has each token removed and placed into a 
postfix queue using an algorithm. When the postfix queue is filled from the infix queue,
The infix queue is copied and the copied queue has its tokens extracted in order. Finally,
a third function is called, which extracts the tokens in the postfix queue and peforms the
desired caculations in the correct order.The results of the calculations are given to the 
token result and is outputted to the user.
*/


#include "prototypes.h"
#include "queue/queueType.h"
#include "stack/stackType.h"
#include "token/token.h"
#include <iostream>

using namespace std;

//Precondition: None
//Postconditon: Output to screen
int main(int argc, char const *argv[])
{
	//variables
	queueType<Token> infixQ;
	queueType<Token> postfixQ;
	stackType<Token> conversionStack, evaluationStack;
	Token infixExpression, result;

	//display information to the user
	cout << endl << endl << string(100, '=') << endl
		<< "This Program will take an infix expression, IE: 1 + 2 * 3 - 4 / 5 + 6,"
		<< endl << "and convert it to a postfix expresion, IE: 1 2 3 * + 4 5 / - 6 +."
		<< endl << "After showing the expression forms, the result will be displayed."
		<< endl << "[ Enter 0 or an expression that evaluates to 0 to exit ]"
		<< endl << string(100, '=') << endl;

	//continously prompt user for infix strings until the result is 0
	do
	{
		//prompt user for a valid infix expression
		cout <<  endl << string(100, '*') << endl;
		cout << "Enter an infix expression [0-Exits]: ";
		cin >> infixExpression;

		//turn the user input into tokens and add them to the infix queue
		populateInfixQ(infixExpression, infixQ);

		//copy the infix queue so the data doesn't get altered when its outputted to the user
		queueType<Token>* tmpInfix =  new queueType<Token>(infixQ);

		//output the infix queue to the user by extracting every token in the tmpInfix queue
		cout << "INFIX QUEUE" << endl;
		while(!tmpInfix->isEmptyQueue())
		{
			Token tmpTok = tmpInfix->front();
			tmpInfix->deleteQueue();
			cout << tmpTok << " ";
		}
		delete tmpInfix;
		tmpInfix = nullptr;

		//turn the infix queue into a postfix queue
		populatePostfixQ(infixQ, postfixQ, conversionStack);

		//copy the postfix queue so the data doesn't get altered when its outputted to the user
		queueType<Token>* tmpPostfix = new queueType<Token>(postfixQ);
		cout << endl << endl << "POSTFIX QUEUE" << endl;
		while(!tmpPostfix->isEmptyQueue())
		{
			Token tmpTok = tmpPostfix->front();
			tmpPostfix->deleteQueue();
			cout << tmpTok << " ";
		}
		delete tmpPostfix;
		tmpPostfix = nullptr;

		//assignt the result of the evaluation of the postfixQ to the Token result and display it to the user
		result = evaluatePostFixExpression(postfixQ, evaluationStack);
		cout << endl << endl << "RESULT: " << result << endl;
	} while (result.Operand() != (double)0);
	
	return 0;
}

