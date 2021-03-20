//File: populatePostfixQ.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog1
//Modified: 01/15/21

/*
Description:
This function will go throug the infixQ from front to back, taking each token from the queue and dermining if it should
go onto the postFixQ queue or the conversion stack. During the algorithm, the function switches between taking items from 
the infixQ queue or stack and putting them into the postfixQ. Eventually every token put into the conversion stack will
be placed into the postfixQ.
*/


#include "../prototypes.h"


//Precondition: A populated infixQ queue and empty postFixQ queue of tokens and an empty conversion stack of tokens
//Postconditon: The infixQ will be empty, the postFixQ will be populated, and the conversion stack will be empty
void populatePostfixQ(queueType<Token>& infixQ, queueType<Token>& postfixQ, stackType<Token>& conversionStack)
{
	//variables
	Token topOfStack, curToken;
	stackType<Token> tmpStack;

	//continuously remove tokens from the infixQ queue until there are none left
	while(!infixQ.isEmptyQueue())
	{
		//the token being evaluated for placement
		curToken = infixQ.front();

		//check if the current token is an operand, IE: "23, 1, 50, 92, etc."
		if (curToken.IsOperand())
		{
			postfixQ.addQueue(curToken);
		}

		//check if the current token is an operator, IE: "+, -, *, /, ^"
		else if (curToken.IsOperator())
		{
			//do not evaluated against the stack if the stack is empty
			if(!conversionStack.isEmptyStack())
			{
				//reference to the token at the top of the stack
				topOfStack = conversionStack.top();

				//take tokens out of the conversion stack and put them into the postfixQ queue until
				//one of the following is true:
				//*The conversion stack has no tokens
				//*The top of the conversion stack is a left parenthesis
				//*The current token from the infixQ queue is an exponential operator
				//*The current token from the infixQ queue has a greater precedence than the token at
				//	the top of the stack.
				while(	!conversionStack.isEmptyStack() && 
						!topOfStack.IsLeftParen() &&
						curToken.Precedence() != 3 && // precedence of 3 is an exponential operator
						!(curToken.Precedence() > topOfStack.Precedence())) 
				{
					topOfStack = conversionStack.top();
					conversionStack.pop();
					postfixQ.addQueue(topOfStack);

					//assign the topOfStack token the new value of the top of the stack or zero if the
					//if the stack is empty. This is used for evaluation in the while loop.
					topOfStack = !conversionStack.isEmptyStack()?conversionStack.top():0;
				}
			}

			//put the current token from infixQ onto the conversion stack
			conversionStack.push(curToken);	
		}

		//check if the current token from infixQ is a left parenthesis. If so put it on the stack
		//this check isn't neeeded because when a right parenthesis is found, the left parentheses
		//are taken from the stack.
		else if (curToken.IsLeftParen()) // "("
		{
			conversionStack.push(curToken);
		}

		//check if the current token from infixQ is a right parenthesis
		else if (curToken.IsRightParen()) // ")"
		{
			//continuously take tokens from the conversion stack and add them to postfixQ unless
			//the token is a left parenthesis, which is ignored and removed.
			do
			{
				if(!conversionStack.isEmptyStack())
				{
					topOfStack = conversionStack.top();
					conversionStack.pop();
					if(!topOfStack.IsLeftParen())
					{
						postfixQ.addQueue(topOfStack);
					}	
				}
			}while(!conversionStack.isEmptyStack());
		}

		//remove the current token from the infixQ queue
		infixQ.deleteQueue();
	}

	//take any tokens remaining on the stack and put them in postfixQ
	while(!conversionStack.isEmptyStack())
	{
		topOfStack = conversionStack.top();
		conversionStack.pop();
		postfixQ.addQueue(topOfStack);
	}
}