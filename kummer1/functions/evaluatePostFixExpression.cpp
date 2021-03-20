//File: evaluatePostFixExpression.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog1
//Modified: 01/15/21

/*
Description:
This function takes in a token queue and stack and returns a token. The token outputted is
the calculation of all the operands and operators in the postfix queue.
*/


#include "../prototypes.h"


//Precondition: A valid postfix queue of tokens and an empty stack of tokens must be provided
//Postconditon: The postfix queue has all tokens removed, the token stack will be empty, and 
//				a token is returned with the evaluation of the postfix queue.
Token evaluatePostFixExpression(queueType<Token>& postfixQ, stackType<Token>& evalStack)
{
	//variables
	Token valOne, valTwo, curToken, tmpVal, result=(int)0;

	//go through the postfix queue until all tokens are removed
	while(!postfixQ.isEmptyQueue())
	{
		//get the value of what of the token at the front of the queue
		curToken = postfixQ.front();

		//check if the token is an operand. If it is, put it in the evaluation stack
		if (curToken.IsOperand()) // operands: "23, 1, 50, 92, etc."
		{
			evalStack.push(curToken);
		}

		//check if the token is an operator. If so, take two tokens from the stack and perform
		//the operation of the current token. Put the result of the operation into the eval stack
		else if (curToken.IsOperator()) // operators: "+, -, *, /, ^"
		{
			valTwo = evalStack.top();
			evalStack.pop();
			valOne = evalStack.top();
			evalStack.pop();

			switch(curToken.Operator())
			{
				case '+' : tmpVal = valOne + valTwo; break;
				case '-' : tmpVal = valOne - valTwo; break;
				case '*' : tmpVal = valOne * valTwo; break;
				case '/' : tmpVal = valOne / valTwo; break;
				case '^' : tmpVal = valOne ^ valTwo; break;
			}

			evalStack.push(tmpVal);
		}


		//If there were any parenthesis, they would be ignored since they are not used in postfix evaluation


		//Remove the token from the front of the queue and process the next token.
		postfixQ.deleteQueue();
	}

	//The last token on the stack is the result of all operations, this value is assigned to the token result
	//and returned to the function call. Also, the last token is removed from the stack.
	result = evalStack.top();
	evalStack.pop();
	return result;
}